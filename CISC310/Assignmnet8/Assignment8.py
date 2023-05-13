#Jonathan Benusa Assignment 05/13/2023
#This program creates 2 different 4 char passwords and then guesses them
#The second password has was more combinations which should make it take longer to guess.

import itertools
import random
import string
import time

def generate_password():
    #really easy library for generating a random passwork of 4 upper case letters
    return ''.join(random.choices(string.ascii_uppercase, k=4))

def brute_force(password):
    #keep track of starting time for guessing
    start = time.time()
    index = 0
    #continue to guessing all combinations until there is a match. repeat 4 means that there are 4 letters long phrases
    for guess in itertools.product(string.ascii_uppercase, repeat=4):
        index = index+1 #index will keep ttrack of the number of guesses
        guess = ''.join(guess)
        #if the guess is correct
        if guess == password:
            guess = ''.join(guess)
            end = time.time()
            #return number of guesses, guess, and time as a touple
            return (index, guess, end - start)
    return None

#functions for more difficult passwords
def generate_complex_password():
    #now all letters plus digits and specified special characters
    return ''.join(random.choices(string.ascii_letters+string.digits+":;><=?@{}\^_", k=4))

def complex_brute_force(password):
    #keep track of starting time for guessing
    start = time.time()
    index = 0
    #continue to guessing all combinations until there is a match. repeat 4 means that there are 4 letters long phrases
    for guess in itertools.product(string.ascii_letters+string.digits+":;><=?@{}\^_", repeat=4):
        index = index+1 #index will keep ttrack of the number of guesses
        guess = ''.join(guess)
        #if the guess is correct
        if guess == password:
            end = time.time()
            #return number of guesses, guess, and time as a touple
            return (index, guess, end - start)
    return None

f = open("Output8.txt", "w")

f.write("Jonathan Benusa Assignment 8 Output file 05/13/2023\n\n")

#create and guess easy password
password = generate_password()
result1 = brute_force(password)
i=0
#write data to output file
f.write(f"Case {i+1}\n")
f.write(f"Password: {password}\n")
f.write(f"Generated password in hex is: {password.encode().hex()}\n")
f.write(f"Guesses: {result1[0]}\n")
f.write(f"Time: {result1[2]} seconds\n")
f.write(f"Guessed Password: {result1[1]}\n\n")

#create complex password and repeat
password = generate_complex_password()
result2 = complex_brute_force(password)
#write data for complex password
f.write(f"Case {i+1}\n")
f.write(f"Password: {password}\n")
f.write(f"Generated password in hex is: {password.encode().hex()}\n")
f.write(f"Guesses: {result2[0]}\n")
f.write(f"Time: {result2[2]} seconds\n")
f.write(f"Guessed Password: {result2[1]}\n\n")

#find time difference 
f.write(f"It took {result2[2]/result1[2]} times as long with the expanded character set to guess the password.")
f.close()

