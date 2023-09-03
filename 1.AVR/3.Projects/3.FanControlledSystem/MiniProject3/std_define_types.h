/*
 * std_define_types.h
 *
 *  Created on: Oct 5, 2022
 *      Author: Dell
 */

#ifndef STD_DEFINE_TYPES_H_
#define STD_DEFINE_TYPES_H_

/* Boolean Values */
#ifndef TRUE
#define TRUE	(1u)
#endif
#ifndef FALSE
#define FALSE	(0u)
#endif

#define HIGH	(1u)
#define LOW		(0u)


#define NULL_PTR    ((void*)0)

/* Boolean Data Type */
typedef unsigned char		bool;

typedef unsigned char		uint8;
typedef signed char			sint8;
typedef unsigned short		uint16;
typedef signed short 		sint16;
typedef unsigned long 		uint32;
typedef signed long			sint32;
typedef unsigned long long	uint64;
typedef signed long long	sint64;
typedef float				float32;
typedef double				double64;



#endif /* STD_DEFINE_TYPES_H_ */
