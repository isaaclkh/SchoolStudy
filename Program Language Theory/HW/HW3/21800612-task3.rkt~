#lang plai

;------------------------------------

;<RCFAEDS> ::= <num>
;        ::= {+ <RCFAEDS> <RCFAEDS>}
;        ::= {- <RCFAEDS> <RCFAEDS>}
;        ::= {* <RCFAEDS> <RCFAEDS>}
;        ::= <id>
;        ::= {fun {<id>} <RCFAEDS>}
;        ::= {<RCFAEDS> <RCFAEDS>}
;        ::= {if <RCFAEDS> <RCFAEDS> <RCFAEDS>}
;        ::= {or <RCFAEDS> <RCFAEDS>}
;        ::= {= <RCFAEDS> <RCFAEDS>}

;------------------------------------

;[contract] run : expression (RCFAEDS) -> result
;[purpose] To simplify getting the result by parsing expression and then interpreting expression with empty Sub
(define (run sexp)
  (interp (parse sexp) (mtSub)))

;[contract] Structure of RCFAEDS
;[purpose] To build the structure of RCFAEDS
(define-type RCFAEDS
  [num (n number?)]
  [add (lhs RCFAEDS?)(rhs RCFAEDS?)]
  [sub (lhs RCFAEDS?)(rhs RCFAEDS?)]
  [mul (lhs RCFAEDS?)(rhs RCFAEDS?)]
  [id (name symbol?)]
  [fun (param symbol?)(body RCFAEDS?)]
  [app (ftn RCFAEDS?)(arg RCFAEDS?)]
  
  [eql (l RCFAEDS?)(r RCFAEDS?)]
  [ifexp (expr RCFAEDS?)(then RCFAEDS?)(else RCFAEDS?)]
  [orop (l RCFAEDS?)(r RCFAEDS?)]
  )

;[contract] parse : expression (sexp) -> abstract code (RCFAEDS)
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
    [else (error 'parse "bad syntax : ~a" sexp)]
    ))

;[contract] DefrdSub : RCFAEDS (DefrdSub) -> number
;[purpose] To use deffered substitution cache (This is the structure of DefrdSub)
(define-type DefrdSub
  [mtSub]
  [aSub (name symbol?)(value RCFAEDS-Value?)(ds DefrdSub?)]
  [aRecSub (name symbol?)
           (value-box (box/c RCFAEDS-Value?))
           (ds DefrdSub?)])

;[contract] This is the types (structure) for RCFAEDS-Value
;[purpose] To use deffered substitution cache
(define-type RCFAEDS-Value
  [numV (n number?)]
  [closureV (param symbol?)
            (body RCFAEDS?)
            (ds DefrdSub?)]
  [exprV (expr RCFAEDS?)(ds DefrdSub?)
         (value (box/c (or/c false RCFAEDS-Value?)))])

;[contract] strict : v (RCFAEDS-Value) -> box v
;[purpose] To store RCFAEDS-Value in box form
(define (strict v)
  (type-case RCFAEDS-Value v
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

;[contract] lookup : symbol (DefrdSub) -> RCFAEDS-Value
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

;[contract] interp : expression (RCFAEDS DefrdSub) -> result (RCFAEDS-Value)
;[purpose] To interprete abstract syntax to result 
(define (interp rlfaeds ds)
  (type-case RCFAEDS rlfaeds
    [num (n) (numV n)]
    [add (l r) (num+ (interp l ds)(interp r ds))]
    [sub (l r) (num- (interp l ds)(interp r ds))]
    [mul (l r) (num* (interp l ds)(interp r ds))]
    [id (name) (lookup name ds)]
    [fun (param body-expr)(closureV param body-expr ds)]
    [app (f a) (local [(define f-val (strict (interp f ds)))
                       (define a-val (exprV a ds (box #f)))
                       (define holder (box (numV 200)))
                       (define new-ds (aRecSub (closureV-param f-val) holder ds))]

                 (begin
                   (set-box! holder (interp a new-ds)))
                 
                 (interp (closureV-body f-val)
                         (aSub (closureV-param f-val)
                               a-val
                               new-ds)))]

    [eql (l r) (eqll (interp l ds)(interp r ds))]
    [ifexp (test-expr then-expr else-expr)
           (if (interp test-expr ds)
           (interp then-expr ds)
           (interp else-expr ds))]
    [orop (l r) (or (interp l ds) (interp r ds))]
    ))

;[test]
;(test (run '{with {fac {fun {n} {if {= n 0} 1 {* n {fac {- n 1}}}}}}{fac 10}}) (numV 3628800))
;(test (run '{with {fib {fun {n} {if {or {= n 0} {= n 1}} 1 {+ {fib {- n 1}} {fib {- n 2}}}}}} {fib 10}})(numV 89))
;(test (run '{with {count {fun {n} {if {= n 0} 0 {+ 1 {count {- n 1}}}}}} {count 8}}) (numV 8))




