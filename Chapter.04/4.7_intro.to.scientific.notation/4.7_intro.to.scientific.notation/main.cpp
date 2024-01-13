//
//  main.cpp
//  4.7_intro.to.scientific.notation
//
//  Created by εκλεγμένοι εν Χριστώ on 9/14/22.
//

/*
 Scientific notation: shorthand for writing lengthy numbers
 in a concise manner. also helps in understanding the working
 on floating point numbers.
 
 form:
        significand x 10^exponent
        1.2         x 10^4
 significand: 1.2
 exponent: 4
 10^4: 10000
 1.2 x 10000: 12000
 
 By convention: numbers in scientific notation are written
 with one digit before the decimal point, and the rest
 of the digits afterward.
 
 example: 5,973,600,000,000,000,000,000,000
 
 scientific notation: 5.9736 x 10^24
 
 in C++: e or E used to represent the "times 10 to the power
 of".
 
 so positive, 5.9736 x 10^24 = 5.9736e24
 so negative, 5 x 10^-2 = 5e-2
 -------------------------------------------------------------
 Converting numbers to scientific notation:
 procedure:
 exponent starts at zero
 slide the decimal: so there is only one non zero digit to the
 left of the decimal
 Each place you slide the decimal to the left increases the exponent by 1.
 Each place you slide the decimal to the right decreases the exponent by 1.
 trim off any leading zeroes on the left end of the
 significand.
 trim off any trailing zeroes on the right end of the
 significand, only if original number has no decimal point
 
 example:
 
 42030
 slide decimal left 4 spaces: 4.2030e4
 no leading zeroes to trim
 trimming trailing zeroes: 4.203e4 - 4 significant digits
 
 0.0078900
 slide decimal right 3 spaces: 0007.8900e-3
 trimming leading zeroes: 7.8900e-3
 don't trim trailing zeroes: 7.8900e-3 - 5 significant digits
 
 600.410
 slide decimal left 2 spaces: 6.00410e2
 no leading zeroes to trim
 don't trim trailing zeroes: 6.00410e2 - 6 significant digits
 
 significant digits: the digits before the e
 precision: no. of significant digits
 more significant digits more the precision of a number
 
 Precision and trailing zeros after the decimal:
 we prefer to keep trailing zeros after a decimal point,
 because those digits impart useful information about the
 precision of the number.
 */
