#lang plai

;------------------------------------

;<RCFAE> ::= <num>
;        ::= {+ <RCFAE> <RCFAE>}
;        ::= {- <RCFAE> <RCFAE>}
;        ::= {* <RCFAE> <RCFAE>}
;        ::= <id>
;        ::= {fun {<id>} <RCFAE>}
;        ::= {<RCFAE> <RCFAE>}
;        ::= {if <RCFAE> <RCFAE> <RCFAE>}
;        ::= {or <RCFAE> <RCFAE>}
;        ::= {= <RCFAE> <RCFAE>}

;------------------------------------

;[contract] run : expression (RCFAE) -> result
;[purpose] To simplify getting the result by parsing expression and then interpreting expression with empty Sub
(define (run sexp)
  (interp (parse sexp) (mtSub)))

;[contract] Structure of RCFAE
;[purpose] To build the structure of RCFAE
(define-type RCFAE
  [num (n number?)]
  [add (lhs RCFAE?)(rhs RCFAE?)]
  [sub (lhs RCFAE?)(rhs RCFAE?)]
  [mul (lhs RCFAE?)(rhs RCFAE?)]
  [id (name symbol?)]
  [fun (param symbol?)(body RCFAE?)]
  [app (ftn RCFAE?)(arg RCFAE?)]
  
  [eql (l RCFAE?)(r RCFAE?)]
  [ifexp (expr RCFAE?)(then RCFAE?)(else RCFAE?)]
  [orop (l RCFAE?)(r RCFAE?)]

  [rec (name symbol?) (named-expr RCFAE?) (fst-call RCFAE?)]
  )

;[contract] parse : expression (sexp) -> abstract code (RCFAE)
;[purpose] To convert concrete code to abstract code
(define (parse sexp)
  (match sexp
    [(? number?)(num sexp)]
    [(list '+ l r)(add (parse l)(parse r))]
    [(list '- l r)(sub (parse l)(parse r))]
    [(list '* l r)(mul (parse l)(parse r))]
    
    [(list 'with (list i v) e) (app (fun i (parse e)) (parse v))]
    [(? symbol?)(id sexp)]
    [(list 'fun (list p) b)(fun p (parse b))]
    [(list f a)(app (parse f)(parse a))]

    [(list '= l r)(eql (parse l)(parse r))]
    
    [(list 'if expr then else) (ifexp (parse expr) (parse then) (parse else))]
    [(list 'or l r) (orop (parse l) (parse r))]

    [(list 'rec name named-expr fst-call) (rec (parse name) (named-expr) (parse fst-call))]
    
    [else (error 'parse "bad syntax : ~a" sexp)]
    ))

;[contract] DefrdSub : RCFAE (DefrdSub) -> number
;[purpose] To use deffered substitution cache (This is the structure of DefrdSub)
(define-type DefrdSub
  [mtSub]
  [aSub (name symbol?)(value RCFAE-Value?)(ds DefrdSub?)]
  [aRecSub (name symbol?)
           (value-box (box/c RCFAE-Value?))
           (ds DefrdSub?)])

;[contract] This is the types (structure) for RCFAE-Value
;[purpose] To use deffered substitution cache
(define-type RCFAE-Value
  [numV (n number?)]
  [closureV (param symbol?)
            (body RCFAE?)
            (ds DefrdSub?)]
  [exprV (expr RCFAE?)(ds DefrdSub?)
         (value (box/c (or/c false RCFAE-Value?)))])

;[contract] strict : v (RCFAE-Value) -> box v
;[purpose] To store RCFAE-Value in box form
(define (strict v)
  (type-case RCFAE-Value v
    [exprV (expr ds v-box)
           (if (not (unbox v-box))
               (local [(define v (strict (interp expr ds)))]
                 (begin (set-box! v-box v) v))
           (unbox v-box))]
    [else v]))

;[contract] num-op : expression (operation) -> numV
;[purpose] to calculate adding, subtracting, and multiplying
(define (num-op op)
  (lambda (x y)(numV (op (numV-n (strict x))(numV-n (strict y))))))

(define num+ (num-op +)) ;[purpose] To sum up two numbers
(define num- (num-op -)) ;[purpose] To subtract up two numbers
(define num* (num-op *)) ;[purpose] To multiply up two numbers

;[contract] eqll : numV-n numV-n -> #t or #f
;[purpose] To find out if two inputs are equal
(define (eqll x y)
  (eq? (numV-n (strict x))(numV-n (strict y))))

;[contract] lookup : symbol (DefrdSub) -> RCFAE-Value
;[purpose] To match the identifiers with looking up the storage
(define (lookup name ds)
  (type-case DefrdSub ds
    [mtSub() (error 'lookup "free identifier")]
    [aSub (i v saved)(if (symbol=? i name)
                         v (lookup name saved))]
    [aRecSub (sub-name val-box rest-ds)
             (if (symbol=? sub-name name)
                 (unbox val-box)
                 (lookup name rest-ds))]))

;[contract] interp : expression (RCFAE DefrdSub) -> result (RCFAE-Value)
;[purpose] To interprete abstract syntax to result 
(define (interp rlfae ds)
  (type-case RCFAE rlfae
    [num (n) (numV n)]
    [add (l r) (num+ (interp l ds)(interp r ds))]
    [sub (l r) (num- (interp l ds)(interp r ds))]
    [mul (l r) (num* (interp l ds)(interp r ds))]
    [id (name) (lookup name ds)]
    [fun (param body-expr)(closureV param body-expr ds)]
    [app (f a) (local [(define f-val (strict(interp f ds)))
                       (define a-val (exprV a ds (box #f)))]
                 (interp (closureV-body f-val)
                         (aSub (closureV-param f-val)
                               a-val
                               (closureV-ds f-val))))]

    [eql (l r) (eqll (interp l ds)(interp r ds))]
    [ifexp (test-expr then-expr else-expr)
           (if (interp test-expr ds)
           (interp then-expr ds)
           (interp else-expr ds))]
    [orop (l r) (or (interp l ds) (interp r ds))]

    [rec (bound-id named-expr fst-call)
      (local [(define value-holder (box (numV 198)))
              (define new-ds (aRecSub bound-id value-holder ds))]
        (begin
          (set-box! value-holder (interp named-expr new-ds))
          (interp fst-call new-ds)))]
    ))

(run '{rec {count {fun {n} {if {= n 0} {+ 1 {count {- n 1}}}}}} {count 8}})

;[test]
;(test (run '{with {fac {fun {n} {if {= n 0} 1 {* n {fac {- n 1}}}}}}{fac 10}}) (numV 3628800))
;(test (run '{with {fib {fun {n} {if {or {= n 0} {= n 1}} 1 {+ {fib {- n 1}} {fib {- n 2}}}}}} {fib 10}})(numV 89))
;(test (run '{with {count {fun {n} {if {= n 0} 0 {+ 1 {count {- n 1}}}}}} {count 8}}) (numV 8))
