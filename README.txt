                                    DS Project - 2019
                        Done By : Nikhil K R and Ruchira R Vadiraj
                              (PES2201800044)     (PES2201800602)
                              
                                Title : A simple spell checker

About :
    Using a trie tree as our dictionary, we've tried to implement a simple spell checker with input in the form of a text file
    and the output,displayed on the terminal. On parsing through the text file word by word, if a word encountered is
    not found in the dictionary, suggestions to correct the misspelt word is done by running a prefix search on the first 
    four characters of the selected word, and printing atmost four words that can replace the misspelt word on the terminal.

Conditions:
    NO UPPER CASE ALLOWED OR ANY OTHER SPECIAL CHARACTERS.
    A space is necessary after entering a word.
    User input is to be typed in user.txt file (Do not enter . , : , ; , ' , " or any special characters)
    To run use : gcc proj.c src.c
    
