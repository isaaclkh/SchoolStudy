#lang plai

;------------------------------------

;<RLFAE> ::= <num>
;        ::= {+ <RLFAE> <RLFAE>}
;        ::= {- <RLFAE> <RLFAE>}
;        ::= {* <RLFAE> <RLFAE>}
;        ::= <id>
;        ::= {fun {<id>} <RLFAE>}
;        ::= {<RLFAE> <RLFAE>}
;        ::= {if <RLFAE> <RLFAE> <RLFAE>}
;        ::= {or <RLFAE> <RLFAE>}
;        ::= {= <RLFAE> <RLFAE>}

;------------------------------------


;[contract] run : expression (BLFAE) -> result
;[purpose] To analyze if the expression needs recursion or not and through that parse and interprete the expression
(define (run sexp)
  (cond
    [(if (equal? (is-recursion sexp) 't)
     (interp (desugar sexp)(mtSub))
     (interp (parse sexp) (mtSub)))]))


;[contract] Structure of RLFAE
;[purpose] To build the structure of RLFAE
(define-type RLFAE
  [num (n number?)]
  [add (lhs RLFAE?)(rhs RLFAE?)]
  [sub (lhs RLFAE?)(rhs RLFAE?)]
  [mul (lhs RLFAE?)(rhs RLFAE?)]
  [id (name symbol?)]
  [fun (param symbol?)(body RLFAE?)]
  [app (ftn RLFAE?)(arg RLFAE?)]
  
  [eql (l RLFAE?)(r RLFAE?)]
  [ifexp (expr RLFAE?)(then RLFAE?)(else RLFAE?)]
  [orop (l RLFAE?)(r RLFAE?)]
  )

;[contract] flat-lift : list of lists -> each of the element matching each list
;[purpose] To support is-in-list function
(define (flat-lift l)
  (match (flatten l)
    ['() '()]
    [(list n number?) (list l)]
    [(cons a (cons b c)) (cons (list a) (flat-lift (list b c)))]))

;[test] : all the elements should come out each
;(flat-lift '{with {fac {fun {n} {if {= n 0} 1 {* n {fac {- n 1}}}}}}{fac 10}})
;(flat-lift '{with {fib {fun {n} {if {or {= n 0} {= n 1}} 1 {+ {fib {- n 1}} {fib {- n 2}}}}}} {fib 10}})

;[contract] is-in-list : list value -> 't or 'f
;[purpose] To return if the list has the value. This will support is-recursion function.
(define (is-in-list list value)
 (cond
  [(empty? list) 'f]
  [(equal? (first list) value) 't]
  [else (is-in-list (rest list) value)]))

;[test]
;(test (is-in-list '{1 2 3 4 5 fun} 'fun) 't)
;(test (is-in-list '{with hi no bye} 'yes) 'f)

;[contract] is-recursion : expression (BLFAE) -> 't or 'f
;[purpose] To return if the expression needs recursive or not.
;[test] : test cases are going to be with the test case of RLFAE (down below)
(define (is-recursion sexp)
  (match sexp
    [(list 'with {list i v} e) (is-in-list (flat-lift v) (list i))]
    [else (parse sexp)]
    ))


;[contract] desugar : expression (BLFAE : sugared expression) -> expression (BLFAE : desugared expression)
;[purpose] To desugar sugared expression
;[test] : test cases are going to be with the test case of RLFAE (down below)
(define (desugar sexp)
  (match sexp
    [(list 'with {list i v} e) (app
                               (fun 'mk-rec (app (fun i (parse e)) (app (id 'mk-rec) (fun i (parse v)))))
                               (fun 'body-proc (app (fun 'fX (app (id 'fX) (id 'fX))) (fun 'fY (app (fun 'f (app (id 'body-proc) (id 'f))) (fun 'x (app (app (id 'fY) (id 'fY)) (id 'x))))))))]
    ))

;[contract] parse : expression (sexp) -> abstract code (RLFAE)
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

;[contract] DefrdSub : RLFAE (DefrdSub) -> number
;[purpose] To use deffered substitution cache (This is the structure of DefrdSub)
(define-type DefrdSub
  [mtSub]
  [aSub (name symbol?)(value RLFAE-Value?)(ds DefrdSub?)]
  [aRecSub (name symbol?)
           (value-box (box/c RLFAE-Value?))
           (ds DefrdSub?)])

;[contract] This is the types (structure) for RLFAE-Value
;[purpose] To use deffered substitution cache
(define-type RLFAE-Value
  [numV (n number?)]
  [closureV (param symbol?)
            (body RLFAE?)
            (ds DefrdSub?)]
  [exprV (expr RLFAE?)(ds DefrdSub?)
         (value (box/c (or/c false RLFAE-Value?)))])

;[contract] strict : v (RLFAE-Value) -> box v
;[purpose] To store RLFAE-Value in box form
(define (strict v)
  (type-case RLFAE-Value v
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

;[contract] lookup : symbol (DefrdSub) -> RLFAE-Value
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

;[contract] interp : expression (RLFAE) -> result (RLFAE-Value)
;[purpose] To interprete abstract syntax to result
(define (interp rlfae ds)
  (type-case RLFAE rlfae
    [num (n) (numV n)]
    [add (l r) (num+ (interp l ds)(interp r ds))]
    [sub (l r) (num- (interp l ds)(interp r ds))]
    [mul (l r) (num* (interp l ds)(interp r ds))]
    [id (name) (lookup name ds)]
    [fun (param body-expr)(closureV param body-expr ds)]
    [app (f a) (local [(define f-val (strict (interp f ds)))
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
    ))


;[test]
;(test (run '{with {fac {fun {n} {if {= n 0} 1 {* n {fac {- n 1}}}}}}{fac 10}}) (numV 3628800)) ;test for RLFAE
;(test (run '{with {fib {fun {n} {if {or {= n 0} {= n 1}} 1 {+ {fib {- n 1}} {fib {- n 2}}}}}} {fib 10}}) (numV 89)) ;test for RLFAE
;(test (run '{with {fac {fun {n} 1}} {fac 5}}) (numV 1)) ; no recursion
;(test (run '{with {fac {fun {n} (+ 1 2)}} {fac 5}}) (numV 3)) ; no recursion
;(test (run '{{fun {x} 0} {+ 1 {fun {y} 2}}}) (numV 0)) ;lazziness test