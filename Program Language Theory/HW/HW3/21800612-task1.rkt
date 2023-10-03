#lang plai
;------------------------------------

;<LFAE> ::= <num>
;        ::= {+ <LFAE> <LFAE>}
;        ::= {- <LFAE> <LFAE>}
;        ::= <id>
;        ::= {fun {<id>} <LFAE>}
;        ::= {<LFAE> <LFAE>}

;------------------------------------

;[contract] run : expression (LFAE) -> result
;[purpose] To simplify getting the result by parsing expression and then interpreting expression with empty Sub
(define (run sexp)
  (interp (parse sexp) (mtSub)))

;[contract] Structure of LFAE
;[purpose] To build the structure of LFAE
(define-type LFAE
  [num (n number?)]
  [add (lhs LFAE?)(rhs LFAE?)]
  [sub (lhs LFAE?)(rhs LFAE?)]
  [id (name symbol?)]
  [fun (param symbol?)(body LFAE?)]
  [app (ftn LFAE?)(arg LFAE?)])

;[contract] parse : expression (sexp) -> abstract code (LFAE)
;[purpose] To convert concrete code to abstract code
(define (parse sexp)
  (match sexp
    [(? number?)(num sexp)]
    [(list '+ l r)(add (parse l)(parse r))]
    [(list '- l r)(sub (parse l)(parse r))]
    [(list 'with (list i v) e) (app (fun i (parse e)) (parse v))]
    [(? symbol?)(id sexp)]
    [(list 'fun (list p) b)(fun p (parse b))]
    [(list f a)(app (parse f)(parse a))]
    [else (error 'parse "bad syntax : ~a" sexp)]))

;[contract] DefrdSub : LFAE (DefrdSub) -> number
;[purpose] To use deffered substitution cache (This is the structure of DefrdSub)
(define-type DefrdSub
  [mtSub]
  [aSub (name symbol?)(value LFAE-Value?)(ds DefrdSub?)])

;[contract] This is the types (structure) for LFAE-Value
;[purpose] To use deffered substitution cache
(define-type LFAE-Value
  [numV (n number?)]
  [closureV (param symbol?)
            (body LFAE?)
            (ds DefrdSub?)]
  [exprV (expr LFAE?)(ds DefrdSub?)
         (value (box/c (or/c false LFAE-Value?)))])

;[contract] strict : v (LFAE-Value) -> box v
;[purpose] To store LFAE-Value in box form
(define (strict v)
  (type-case LFAE-Value v
    [exprV (expr ds v-box)
           (if (not (unbox v-box))
               (local [(define v (strict (interp expr ds)))]
                 (begin (set-box! v-box v)
                         v))
                 (unbox v-box))]
    [else v]))

;[contract] num-op : expression (operation) -> numV
;[purpose] to calculate adding, subtracting, and multiplying
(define (num-op op x y)
  (lambda (x y)(numV (op (numV-n (strict x))(numV-n (strict y))))))

(define (num+ x y) (num-op + x y)) ;[purpose] To sum up two numbers
(define (num- x y) (num-op - x y)) ;[purpose] To subtract up two numbers


;[contract] lookup : symbol (DefrdSub) -> LFAE-Value
;[purpose] To match the identifiers with looking up the storage
(define (lookup name ds)
  (type-case DefrdSub ds
    [mtSub() (error 'lookup "free identifier")]
    [aSub (i v saved)(if (symbol=? i name)
                         v (lookup name saved))]))

;[contract] interp : expression (LFAE DefrdSub) -> result (LFAE-Value)
;[purpose] To interprete abstract syntax to result 
(define (interp lfae ds)
  (type-case LFAE lfae
    [num (n) (numV n)]
    [add (l r) (num+ (interp l ds)(interp r ds))]
    [sub (l r) (num- (interp l ds)(interp r ds))]
    [id (name) (lookup name ds)]
    [fun (param body-expr)(closureV param body-expr ds)]
    [app (f a) (local [(define f-val (strict(interp f ds)))
                       (define a-val (exprV a ds (box #f)))]
                 (interp (closureV-body f-val)
                         (aSub (closureV-param f-val)
                               a-val
                               (closureV-ds f-val))))]))

;[test]
;(test (run '{{fun {x} 0} {+ 1 {fun {y} 2}}}) (numV 0))
;(test (run '{{fun {x} 9} {+ {fun 1} 2}}) (numV 9))

(run '{{fun {x} x} {+ 1 {fun {y} 2}}})