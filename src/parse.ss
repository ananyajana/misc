;;------------------------------------------------------
;;
;;  P R O J E C T  1 :  R E A L L Y - T I N Y   
;;    T Y P E   R E C O N S T R U C T I O N
;;
;;             CS515  Fall 2018
;;------------------------------------------------------

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                  Parser
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; author: Ananya Jana

(define CurrentCounter 0)

(define newtvar
   (lambda()
      (set! CurrentCounter (+ CurrentCounter 1))
      (string->symbol (string-append "_a" (number->string CurrentCounter)))))

(define name?
  (lambda (s)
    (and (symbol? s)
         (not (memq s '(lambda))))))

(define parse
  (lambda (m)
    (cond
      ((number? m)  `(&const ,m))
      ((eq? #t m)   `(&const true))
      ((eq? #f m)   `(&const false))
      ((name? m)    `(&var ,m))
      ((pair? m)    (cond 
                      ((eq? `lambda (car m))
                        (if (and (= 3 (length m))
                                 (list? (cadr m))
                                 (= 1 (length (cadr m)))
                                 (name? (caadr m)))
                            `(&lambda ,(cadr m) ,(parse (caddr m)))
                            (error 'parse "Syntax error")))
                      (else
                        `(&apply ,(parse (car m)) ,(parse (cadr m))))))
      (else         (error 'parse "Syntax error")))))


;; PROGRAMMING  SET 3

;; Finite Functions or key-value pairs

;; empty list

(define empty-list '())

;; insert

(define insert
  (lambda (x v l)
    (cons (list x v) l)))

;; look-up   --- you may use assq

(define lookup
  (lambda (x l)
    (let
	((res (assq x l)))
      (cond
       ((pair? res) (cadr res))
       ;(else (error 'lookup "no valid entry"))))))
       (else empty-list)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                     Initial Environments
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define init_E  ;; Type Environment 
  '((add1 (int -> int))
    (sub1 (int -> int))
    (zero? (int -> bool))
    (not (bool -> bool))
    (and (bool -> (bool -> bool)))
    (or (bool -> (bool -> bool)))))

;(define init_C '()) ;; Type Constraints
(define init_C '()) ;; Type Constraints

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                     Type reconstruction
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define TR
  (lambda (ast E C)
    (cond
     ((eq? (and (eq? (car ast) '&const)(number? (cadr ast)))'#t) (cons 'int C))
     ((eq? (and (eq? (car ast) '&const)(not (number? (cadr ast))))'#t) (cons 'bool C))
     ((eq? (car ast) '&var) (if(eq? (lookup (cadr ast) E) empty-list) (cons (lookup (cadr ast) (insert (cadr ast) (newtvar) E)) C)
                               (cons (lookup (cadr ast) E) C)))
     ((eq? (car ast) '&lambda) (let*
                                   ((E1 (insert (caadr ast) (newtvar) E))
                                   (a1 (lookup (caadr ast) E1)))
                                 (cons (cons (lookup (caadr ast) E1) (cons '-> (TR (caddr ast) (insert (caadr ast) (newtvar) E) C))) C ))) 
     ;((eq? (car ast) '&lambda) (TR (caddr ast) (insert (caadr ast) (newtvar) E) C))
     ;((eq? (car ast) '&apply) (cons (TR ( cadr ast) E C) (TR (caddr ast) E C)))
     ;((eq? (car ast) '&apply) (insert (car (TR ( cadr ast) E C)) '((newtvar) -> (newtvar)) C) (TR (caddr ast) E C))
     ((eq? (car ast) '&apply) (if(unify
                                  ((caar (TR ( cadr ast) E C)) (car (TR (caddr ast) E C)) C))
                                       (cons (car (cdr (cdr (car (TR ( cadr ast) E C))))) C)
                                       (error ’unify "*** type conflict ***")))
     (error 'TR: "still an empty body")))) ;; YOUR CODE GOES HERE

(define TRec
  (lambda (m)
       ;;; extract type expression from compound return type(
     ;(car  (TR (parse m) init_E init_C))))
    (TR (parse m) init_E init_C)))

(define unify
  (lambda (e1 e2 set)
    ('hi)))
    
(define (unify_var var val frame)
    (if (equal? var val)                                    
        frame                                               
        (let ((value-cell (binding-in-frame var frame)))    
            (if (not value-cell)                           
                (if (freefor? var val frame)                
                    (extend var val frame)                 
                    #f)                                    
                (unify (binding-value value-cell)           
                    val
                    frame)))))

(define (unify p1 p2 frame)
    (cond
        ((eq? frame #f) #f)                             
        ((var? p1) (unify_var p1 p2 frame))             
        ((var? p2) (unify_var p2 p1 frame))             
        ((constant? p1)                                 
         (if (constant? p2)
             (if (=_constant? p1 p2) frame #f)
             #f))
        ((constant? p2) #f)                             
        (else                                           
            (unify (cdr p1)                             
                (cdr p2)
                (unify                                  
                    (car p1)
                    (car p2)
                    frame)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                        Sample Test cases
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define M1 '((lambda (x) x) 5))
(define M2 '((lambda (x) (sub1 x)) 5))
(define M3 '((lambda (x) 1) ((lambda (x) (x x)) (lambda (x) (x x)))))
(define M4 '((lambda (x) ((and x) #f)) #t))
(define M5 5)
(define M6 true)
(define M7 false)
(define M8 'xyz)
(define M9 'add1)
(define M10 '(x 1))
(define M11 'and)
(define M12 '(add1 1))
;;(define M9 and)
;;(define M9 '(and true true)) This cannot appear
