#lang plai

;---------------------------------------------

;Problem 1
;Solved by myself
;Time taken: about 1 min.

;[contract] dollar->won : number->number
;[purpose] To convert dollar to won
;[tests] (test (dollar->won 100) 134200)

(define (dollar->won n)
  (* n 1342))

;---------------------------------------------

;Problem 2
;Solved by myself
;Time taken: about 1 min.

;[contract] digit_sum :  number number number->number
;[purpose] To sum three integer numbers
;[tests] (test (digit_sum 1 2 3) 6)

(define (digit_sum num1 num2 num3)
  (+ num1 num2 num3))

;---------------------------------------------

;Problem 3
;Solved by myself (Searched for pi function in racket
;from https://docs.racket-lang.org/reference/generic-numbers.html
;and also searched for volume of sphere formula from google.)
;Time taken: about 6 min (almost spent time searhing)

;[contract] volume-sphere : number->number
;[purpose] To figure volume of sphere through radius
;[tests] (test (volume-sphere 3) 113.097335529232548)

(define (volume-sphere n)
  (* 4/3 pi n n n))

;---------------------------------------------

;Problem 4
;Solved by myself (Searched for modulo function in racket
;from https://docs.racket-lang.org/reference/generic-numbers.html
;Time taken: about 3 min.

;[contract] is-even? : number->boolean
;[purpose] To find out the number given is even number
;[tests] (test (is-even? 3) false)

(define (is-even? n)
  (= (modulo n 2) 0))

;---------------------------------------------

;Problem 5
;Solved by myself (Searched for combination formula
;from https://www.statisticshowto.com/probability-and-statistics/probability-main-index/permutation-combination-formula/)
;Time taken: about 8 min. (almost spent time with factorial function)

;[contract] factorial : number -> number
;[purpose] To calculate factorial number of the given number
;[tests] (test (factorial 4) 24)

(define (factorial n)
  (cond
    [(= n 0) 1]
    [else (* n (factorial (- n 1)))]))

;[contract] combination : number number->number
;[purpose] To calculate the number of combinations than can be
;[tests] (test (combination 8 2) 28)

(define (combination n k)
  (/ (factorial n) (* (factorial k) (factorial(- n k)))))

;---------------------------------------------

;Problem 6
;Solved by myself (Searched for and operation in Racket from
;https://docs.racket-lang.org/reference/if.html#%28form._%28%28lib._racket%2Fprivate%2Fletstx-scheme..rkt%29._and%29%29
;Time taken: about 32 min. (Kind of confused because I think I am not yet familiar with this language, Racket)

;a
;structure of Vechicle

(define-type Vehicle
  (Bicycle (wheels number?))
  (Car (wheels number?)
       (windows number?))
  (Airplane (wheels number?)
            (windows number?)
            (engines number?)))

;b
;[contract] vehicle-tax : define-type number number number -> number
;[purpose] To calculate the tax for certain vehicle and to know if the vehicle is safe (check if the vehicle fits the regulations)
;[test]
;(define myBicycle (Bicycle 2))
;(define myCar (Car 4 4))
;(define myAirplane (Airplane 2 6 4))
;(vehicle-tax myBicycle 3 3 3)
;(vehicle-tax myCar 5 6 7)
;(vehicle-tax myAirplane 8 9 1)

(define (vehicle-tax v twh twin ten)
  (type-case Vehicle v
    [Bicycle (wh) (* twh wh)]
    [Car (wh wi) (+ (* wh twh) (* wi twin))]
    [Airplane (wh wi en) (+ (* wh twh) (* wi twin) (* en ten))]))

;c
;[contract] is-vehicle-safe : define-type -> boolean
;[purpose] To calculate the tax for certain vehicle and to know if the vehicle is safe (check if the vehicle fits the regulations)
;[test]
;(define myBicycle (Bicycle 3))
;(define myCar (Car 4 3))
;(define myAirplane (Airplane 3 11 2))
;(is-vehicle-safe myBicycle)
;(is-vehicle-safe myCar)
;(is-vehicle-safe myAirplane)

(define (is-vehicle-safe v)
  (type-case Vehicle v
    [Bicycle (wh) (< wh 4)]
    [Car (wh wi) (and (> wh 3)(> wi 2))]
    [Airplane (wh wi en) (and (> wh 2) (> wi 10) (> en 1))]))

;---------------------------------------------

;Problem 7
;Solved by myself (Searched for list operations
;from https://docs.racket-lang.org/reference/pairs.html
;Time taken: 20 min. (Struggled by using list operations and equality function in racket.)

;[contract] update-name : string string list->list
;[purpose] To produce a list of symbols by replacing all occurences of old by new
;[test] (test (update-name 'cherry 'claire (cons 'jc (cons 'cherry (cons 'kate empty)))) '(jc claire kate))

(define (update-name old new lt)
  (cond
    [(equal? (first lt) old) (append (list new)(rest lt))]
    [else (append (list (first lt))(update-name old new (rest lt)))]))

;---------------------------------------------

;Problem 8
;Solved by myself
;Time taken: about 3hours. (Take to much time studying about the list in racket
;from https://docs.racket-lang.org/reference/pairs.html
;and also searched for binary algorithm
;from https://cjh5414.github.io/binary-search/)

;middle function
;[contract] middle : number number -> number
;[purpose] To find the middle index of the list
;[test] (test (middle 0 7) 3)

(define (middle bot top)
  (cond
    [(even? (+ bot top)) (/ (+ bot top) 2)]
    [else (/ (- (+ bot top) 1) 2)]))

;binary-recur function
;[contract] binary-recur : list number number number -> list
;[purpose] To do the binary search recursively with the numbers of the top and the bottom
;of the list for the calculation throught the information given by binary-search function

(define (binary-recur lst bot top target)
  (cond
    [(> (list-ref lst (middle bot top)) target) (append (list (list-ref lst (middle bot top))) (binary-recur lst bot (- (middle bot top) 1) target))] ;left-side
    [(< (list-ref lst (middle bot top)) target) (append (list (list-ref lst (middle bot top))) (binary-recur lst (+ 1 (middle bot top)) top target))] ;rigtht-side
    [(= (list-ref lst (middle bot top)) target) (list target)]))

;binary-search function (*)
;[contract] binary-search : list number -> list
;[purpose] To find the target number in ascending ordered list through binay search algorithm
;[test]
;(test (binary-search '(1 2 3) 3) '(2 3))
;(test (binary-search '(1 2 3 4 5 6 7 8) 3) '(4 2 3))
;(test (binary-search '(1 2 3 4 5 6 7 8 9 10) 9) '(5 8 9))
;(test (binary-search '(1 2 3 4 5 6 7) 6) '(4 6))
;(test (binary-search '(1 2 3 4 5 6 7 8 9) 4) '(5 2 3 4))
;(test (binary-search '(1 2 3 4 5 6 7 8 9) 3) '(5 2 3))

(define (binary-search lst target)
  (binary-recur lst 0 (- (length lst) 1) target))

;---------------------------------------------