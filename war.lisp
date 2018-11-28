; : It calls shuffle-deck to do the actual shuffling.

(defun shuffle ()



"shuffle returns a list of 52 cards which are in random order"

(shuffle-deck '((two spades) (three spades) (four spades) (five spades)

(six spades) (seven spades) (eight spades) (nine spades)

(ten spades) (jack spades) (queen spades) (king spades) (ace spades)

(two diamonds) (three diamonds) (four diamonds) (five diamonds)

(six diamonds) (seven diamonds) (eight diamonds) (nine diamonds)

(ten diamonds) (jack diamonds) (queen diamonds) (king diamonds)

(ace diamonds)

(two hearts) (three hearts) (four hearts) (five hearts)

(six hearts) (seven hearts) (eight hearts) (nine hearts)

(ten hearts) (jack hearts) (queen hearts) (king hearts) (ace hearts)

(two clubs) (three clubs) (four clubs) (five clubs)

(six clubs) (seven clubs) (eight clubs) (nine clubs)

(ten clubs) (jack clubs) (queen clubs) (king clubs) (ace clubs) )))

;; shuffle-deck begins with the full deck.

;; A random card is called from the deck and placed on the shuffled deck.

;; shuffle-deck is called with the remaining deck.

;;



(defun shuffle-deck (deck)

(cond ((equal nil deck) nil)

(t (let ((index (random (length deck))))

    (cons (nth index deck)

   (shuffle-deck (append (subseq deck 0 index)

(subseq deck (1+ index)))))))))



;;

;;get-suit looks at the second element of the symbols which identify

;; a card '(five clubs).





(defun get-suit (card)

(cadr card))



;;

;; get-rank looks at the first element of the symbols which identify a card

(defun get-rank (card)

(car card))





;;print-card prints the name of the rank and the name of the suit



(defun print-card (card)

(format t "~a of ~a~%" (get-rank card) (get-suit card))
)



;; print-deck sends print-card a card and removes that card from the deck. print-deck is called with the remaining deck



(defun print-deck (deck)

(cond ((equal nil deck) nil)

(t (print-card (car deck))

(print-deck (cdr deck)))))



;; card-deal runs it
(defun card-deal ()

(print-deck (shuffle)))


; This function returns a number for each of the cards so that they can be compared
(defun getNum(numString)

(cond ((equal nil numString) nil)

((equal numString 'two) 2)
((equal numString 'three) 3)
((equal numString 'four) 4)
((equal numString 'five) 5)
((equal numString 'six) 6)
((equal numString 'seven) 7)
((equal numString 'eight) 8)
((equal numString 'nine) 9)
((equal numString 'ten) 10)
((equal numString 'jack) 11)
((equal numString 'queen) 12)
((equal numString 'king) 13)
((equal numString 'ace) 14)

)

)

(defun compare-cards (card1 card2)

(cond ((equal nil card1) nil)

((equal nil card2) nil)
((equal nil card1) nil)
((> (getNum card1) (getNum card2)) card1)
((> (getNum card2) (getNum card1)) card2)

)

)

(defun threw-deck(deck1 deck2)

(cond

  ((equal nil deck1) (print "Player 2 won") nil)

  ((equal nil deck2) (print "Player 1 won") nil)

  ((> (getNum (get-rank (car deck1))) (getNum (get-rank (car deck2))))
  (format t "~a beats ~a~%" (car deck1) (car deck2))
  (threw-deck (append (cdr deck1) (car deck1) (car deck2)) (cdr deck2)) )


  ((< (getNum (get-rank (car deck1))) (getNum (get-rank (car deck2))))
  (format t "~a beats ~a~%" (car deck2) (car deck1))
  (threw-deck (cdr deck1) (append (cdr deck2) (car deck1) (car deck2)) ) )


  ((equal (get-rank (car deck1)) (get-rank (car deck2))) (print "equal"))

)

)

;( defun split-deck ((deckA) (deckB))

;  (cond ((equals (list-length deckA) 26) (deckA) (deckB) )
;        (t (split-deck (cdr deckA) (append (car deckA) deckB ) ) )

;  )

;)

;(defun test-split()
;    (split-deck (shuffle) nil)
;)

( defun play-war()

  (threw-deck (shuffle) (shuffle))

)



; formatT to print
; Compare two hands

;; psudo for war:
;; create two shuffled decks
;; recurse through each of the decks
;; compare the two cards shown and add the both cards back into the winning hand's list
;;
;; if the cards have the same value put both cards back at the bottom of their own list and continue (for now)
;; call war where you pull out three cards and compare the last one and winner takes all of them
;; continue this until one of the decks is empty
