/*
 * @file bit_math.h
 *
 *  @date Jul 1, 2023
 *  @author  Ali Shabana
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT)	(REG |= (1<<BIT))

#define CLEAR_BIT(REG,BIT)	(REG &= ~(1<<BIT))

#define GET_BIT(REG,BIT)	(1 & (REG>>BIT))

#define CHANGE_BIT_VAL(REG, BIT, VAL)	(REG = (REG & ~(1 << (BIT))) | ((VAL) << (BIT)))

#endif /* BIT_MATH_H_ */
