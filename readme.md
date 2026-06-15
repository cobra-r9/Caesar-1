# Caesar-1

This is a detailed implementation of the chiper (a form of primitive encryption) used by Julius Caesar. This involves simply the shift of the alphabetical characters in a cycle, where that shift is known as the *key*. This chiper is one of the ancient chipers in the world and can be simply decrypted via brute force itself.

## Mathematical Foundations of the Chiper 

This is the basic definition of division and the remainder : *For any integer a and positive integer n, there exists unique integers q and r such that a = qn + r*. The mod operation just calculates the remainder. That is the mod is just `r:a mod n = a - n[a/n]`. 

>[!NOTE]
> This is just the modular arithmetics in action. Modular arithmetic modulo m consists of systematically replacing the results of additions, multiplications, and subtractions by the remainder of the division by m. Here, the numbers wrap around when reaching or exceeding a certain value, called the modulus. 

### Example of a modular arithmetic

A familiar setting exhibiting modular arithmetic is the clock's hour hand on a 12 hour clock. As there are 24 hours, we just denote the AM and PM respectively. Suppose the clock hand is currently at 5. After 10 hours, where will the clock's hand point to? In normal addition, it would result in 10 + 5 = 15; dope, its correct by the international format : it would be 15, but we are in a 12 hour format. We need to divide the addition by the 12 and we shall get the remainder; and the remainder is the answer.

**The time in 12 hour clock can be represented by :**

`(current time + hours after) mod 12`

where, current time is the time present, the hours after represents the number of hours after we need to find the time. But what is the range of the modulo function? In general, when considering the modulo function, we see, we have this form : 

`x mod n`

in this case, the range is between 0 to n - 1; ie the answer is zero if x is exactly divisible by n and at most, the highest remainder can reach n - 1.

## Building the Chiper

Now that we know how modulo works and what its range is, we shall begin the process of constructing the modern caesar chiper. We know that the alphabets are 26 in number and we add some key to the plaintext to shift it. What if the added value exeeds the range of alphabets? We need it to **wrap around**; And this wrapping around has a lot to do with **modulo**.

But in `C` programming, we are gonna use the ascii representation of the characters. And here, the characters are just numbers. But `A` does not have a index 1 like in normal alphabets in english. `A` is 65 and `Z` is 90. `a` is 97 and `z` is 122. So here we have two sets of alphabets : Uppercase and Lowercase respectively.

The first step in building the chiper is **normalise the chiper into the range of the modulo operation we are performing.** This sentence has one important detail : the range of the modulo operation. This is because : encryption and decryption simply would not be invertible functions if our normalised character set is not in the range of modulo, and we encrypt, not able to decrypt it. 

### Normalisation 

Here we have two sets of alphabets to normalise. Set `A` to `Z` and set `a` to `z`.
Essentially, we want the value of `A` and `a` to be zero and the value of `Z` and `z` to be 25. (which in fact is in the range of modulo : x modulo 26 belongs to {0..25}); overall total 26 values including both the ends. 

- let `p` be the plaintext character.
- let `n` be the normalised character.

**Case 1** : Character belongs to set 1 : A to Z

In this case, 
- n = p - 'A'
where, 'A' implies the ascii value of A; 

**Case 2** : Character belongs to set 2 : a to z

In this case, 
- n = p - 'a'
where, 'a' implies the ascii value of a;

### Encryption 

- let `x` be the normalised index value of the encrypted character n. 
- let `k` be the key, which is an integer which would shift the character by k.
- then, the index value `x` is provided by the following formula : 

```txt 
x = (n + k) mod 26 
```

- but still, the x is in range 0 to 25 only. It is normalised, and is not in the ascii range. 
- the next step includes de-normalisation of the index to ascii value. This provides us the chipertext.
- let `c` be the cipertext. 

depending on the alphabets whether it is upper or lower case, we use the below given formula to create the chiper character - `c`

```txt 
c = 'A' + x (or) 'a' + x
```

### Decryption 

- this is just the reverse of what we have done after normalisation.
- normalise the chiperchar, call it `x`
- now find the plaintext char, call it `n`
- `n` can be found by the following formula : 

```txt
n = (x - k) mod 26
```

- After finding the normalised plaintext, de-normalise it as the following based on the context.

```txt 
p = 'A' + 'n' (or) 'a' + n 
```


**And yay, we have just completed our first chiper. Good to go.**
