/*
                              *******************
******************************* C SOURCE FILE *******************************
**                            *******************                          **
**                                                                         **
** project  : CGRA-X-HEEP                                                  **
** filename : reversebits.c                                                 **
** version  : 1                                                            **
** date     : 2023-06-22                                                       **
**                                                                         **
*****************************************************************************
**                                                                         **
** Copyright (c) EPFL                                                      **
** All rights reserved.                                                    **
**                                                                         **
*****************************************************************************
*/

/***************************************************************************/
/***************************************************************************/

/**
* @file   reversebits.c
* @date   2023-06-22
* @brief  A description of the kernel...
*
*/

#define _REVERSEBITS_C

/****************************************************************************/
/**                                                                        **/
/*                             MODULES USED                                 */
/**                                                                        **/
/****************************************************************************/
#include <stdint.h>

#include "reversebits.h"
#include "function.h"

/****************************************************************************/
/**                                                                        **/
/*                        DEFINITIONS AND MACROS                            */
/**                                                                        **/
/****************************************************************************/

#define N_BITS 32

#if CGRA_N_COLS == 2

#define CGRA_COLS       2
#define IN_VAR_DEPTH    1
#define OUT_VAR_DEPTH   1

/****************************************************************************/
/**                                                                        **/
/*                      PROTOTYPES OF LOCAL FUNCTIONS                       */
/**                                                                        **/
/****************************************************************************/


    static void        config  (void);
    static void        software(void);
    static uint32_t    check   (void);

    /****************************************************************************/
    /**                                                                        **/
    /*                            GLOBAL VARIABLES                              */
    /**                                                                        **/
    /****************************************************************************/

    const uint32_t  cgra_imem_reve[CGRA_IMEM_SIZE] = {  0xa80000, 0x10080000, 0x1a300001, 0x0, 0x0, 0xc80000, 0x10080000, 0x0, 0x4a080001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10080000, 0x10080000, 0x5a400001, 0x21480000, 0x10b00000, 0x0, 0xa90000, 0x50080000, 0x3a280001, 0x56880001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  };
    static uint32_t cgra_kmem_reve[CGRA_KMEM_SIZE] = {  0x0, 0x3005, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    };

    static int32_t cgra_input[CGRA_COLS][IN_VAR_DEPTH]     __attribute__ ((aligned (4)));
    static int32_t cgra_output[CGRA_COLS][OUT_VAR_DEPTH]   __attribute__ ((aligned (4)));

    static uint32_t	i_index_soft;
    static uint32_t	i_index_cgra;
    static uint32_t	i_NumBits_soft;
    static uint32_t	i_NumBits_cgra;

    static uint32_t	o_ret_soft;
    static uint32_t	o_ret_cgra;


    /****************************************************************************/
    /**                                                                        **/
    /*                           EXPORTED VARIABLES                             */
    /**                                                                        **/
    /****************************************************************************/

    extern kcom_kernel_t reve_kernel = {
        .kmem   = cgra_kmem_reve,
        .imem   = cgra_imem_reve,
        .col_n  = CGRA_COLS,
        .in_n   = 1,
        .out_n  = 1,
        .input  = cgra_input,
        .output = cgra_output,
        .config = config,
        .func   = software,
        .check  = check,
        .name   = "Reversebits",
    };

    /****************************************************************************/
    /**                                                                        **/
    /*                            LOCAL FUNCTIONS                               */
    /**                                                                        **/
    /****************************************************************************/

    void config()
    {
        i_index_soft = kcom_getRand() % (UINT_MAX - 1 - 0 + 1) + 0;
        i_index_cgra = i_index_soft;
        i_NumBits_soft = N_BITS;
        i_NumBits_cgra = i_NumBits_soft;
        cgra_input[0][0] = i_index_cgra;
        cgra_input[1][0] = i_NumBits_cgra;

    }

    void software(void)
    {
        o_ret_soft = reversebits( i_index_soft, i_NumBits_soft );
    }

    uint32_t check(void)
    {
        uint32_t errors = 0;

        o_ret_cgra = cgra_output[0][0];


    #if PRINT_CGRA_RESULTS
        PRINTF("------------------------------\n");
        for( uint8_t c = 0; c < CGRA_COLS; c ++)
        {
            for( uint8_t r = 0; r < OUT_VAR_DEPTH; r++ )
            {
                PRINTF("[%d][%d]:%08x\t\t",c,r,cgra_output[c][r]);
            }
            PRINTF("\n");
        }
    #endif //PRINT_CGRA_RESULTS


    #if PRINT_RESULTS
            PRINTF("\nCGRA\t\tSoft\n");
    #endif

        for( int i = 0; i < 1; i++ )
        {
    #if PRINT_RESULTS
            PRINTF("%08x\t%08x\t%s\n",
            o_ret_cgra,
            o_ret_soft,
            (o_ret_cgra != o_ret_soft) ? "Wrong!" : ""
            );
    #endif

            if (o_ret_cgra != o_ret_soft) {
                errors++;
            }
        }
        return errors;
    }





#elif CGRA_N_COLS == 3

    #define CGRA_COLS       3
    #define IN_VAR_DEPTH    1
    #define OUT_VAR_DEPTH   1

    /****************************************************************************/
    /**                                                                        **/
    /*                      PROTOTYPES OF LOCAL FUNCTIONS                       */
    /**                                                                        **/
    /****************************************************************************/

    static void        config  (void);
    static void        software(void);
    static uint32_t    check   (void);

    /****************************************************************************/
    /**                                                                        **/
    /*                            GLOBAL VARIABLES                              */
    /**                                                                        **/
    /****************************************************************************/

    const uint32_t  cgra_imem_reve[CGRA_IMEM_SIZE] = {  0x0, 0x0, 0x0, 0x0, 0x0, 0xc80000, 0x10080000, 0x0, 0x3a080001, 0x0, 0x0, 0x0, 0x0, 0x20080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0x0, 0x0, 0x46880001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2a280001, 0x0, 0x0, 0x0, 0x10080000, 0x30080000, 0x0, 0x23480000, 0x10b00000, 0x0, 0xa80000, 0x20080000, 0x2a400001, 0x2a300001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  };
    static uint32_t cgra_kmem_reve[CGRA_KMEM_SIZE] = {  0x0, 0x7005, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    };

    static int32_t cgra_input[CGRA_COLS][IN_VAR_DEPTH]     __attribute__ ((aligned (4)));
    static int32_t cgra_output[CGRA_COLS][OUT_VAR_DEPTH]   __attribute__ ((aligned (4)));

    static uint32_t	i_index_soft;
    static uint32_t	i_index_cgra;
    static uint32_t	i_NumBits_soft;
    static uint32_t	i_NumBits_cgra;

    static uint32_t	o_ret_soft;
    static uint32_t	o_ret_cgra;


    /****************************************************************************/
    /**                                                                        **/
    /*                           EXPORTED VARIABLES                             */
    /**                                                                        **/
    /****************************************************************************/

    extern kcom_kernel_t reve_kernel = {
        .kmem   = cgra_kmem_reve,
        .imem   = cgra_imem_reve,
        .col_n  = CGRA_COLS,
        .in_n   = 1,
        .out_n  = 1,
        .input  = cgra_input,
        .output = cgra_output,
        .config = config,
        .func   = software,
        .check  = check,
        .name   = "Reversebits",
    };

    /****************************************************************************/
    /**                                                                        **/
    /*                            LOCAL FUNCTIONS                               */
    /**                                                                        **/
    /****************************************************************************/

    void config()
    {
        i_index_soft = kcom_getRand() % (UINT_MAX - 1 - 0 + 1) + 0;
        i_index_cgra = i_index_soft;
        i_NumBits_soft = N_BITS;
        i_NumBits_cgra = i_NumBits_soft;
        cgra_input[1][0] = i_NumBits_cgra;
        cgra_input[2][0] = i_index_cgra;

    }

    void software(void)
    {
        o_ret_soft = reversebits( i_index_soft, i_NumBits_soft );
    }

    uint32_t check(void)
    {
        uint32_t errors = 0;

        o_ret_cgra = cgra_output[1][0];


    #if PRINT_CGRA_RESULTS
        PRINTF("------------------------------\n");
        for( uint8_t c = 0; c < CGRA_COLS; c ++)
        {
            for( uint8_t r = 0; r < OUT_VAR_DEPTH; r++ )
            {
                PRINTF("[%d][%d]:%08x\t\t",c,r,cgra_output[c][r]);
            }
            PRINTF("\n");
        }
    #endif //PRINT_CGRA_RESULTS


    #if PRINT_RESULTS
            PRINTF("\nCGRA\t\tSoft\n");
    #endif

        for( int i = 0; i < 1; i++ )
        {
    #if PRINT_RESULTS
            PRINTF("%08x\t%08x\t%s\n",
            o_ret_cgra,
            o_ret_soft,
            (o_ret_cgra != o_ret_soft) ? "Wrong!" : ""
            );
    #endif

            if (o_ret_cgra != o_ret_soft) {
                errors++;
            }
        }
        return errors;
    }




#elif CGRA_N_COLS == 4

    #define CGRA_COLS       4
    #define IN_VAR_DEPTH    2
    #define OUT_VAR_DEPTH   1

    /****************************************************************************/
    /**                                                                        **/
    /*                      PROTOTYPES OF LOCAL FUNCTIONS                       */
    /**                                                                        **/
    /****************************************************************************/

    static void        config  (void);
    static void        software(void);
    static uint32_t    check   (void);

    /****************************************************************************/
    /**                                                                        **/
    /*                            GLOBAL VARIABLES                              */
    /**                                                                        **/
    /****************************************************************************/

    #define OPTIMIZED
    #ifdef OPTIMIZED
    const uint32_t  cgra_imem_reve[CGRA_IMEM_SIZE] = {  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc80000, 0x0, 0x5a28000c, 0x0, 0x5b80000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc80000, 0x0, 0x0, 0x0, 0xa008000c, 0x0, 0xa3080800, 0x0, 0x0, 0x0, 0x42880006, 0x0, 0x5a29000c, 0xa6080808, 0x0, 0x0, 0x0, 0x0, 0x0, 0x90000, 0x2a28000c, 0x80000, 0x0, 0x0, 0x0, 0x54490000, 0x0, 0x0, 0x0, 0x62c00000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa008000c, 0x0, 0xa4080804, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80000, 0x0, 0x0, 0x4b90000, 0x600b0000, 0x0, 0x7a310001, 0xa008000c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2a400001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x90000, 0x0, 0x600b0000, 0x7a090001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x50090000, 0x6a280001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
    static uint32_t cgra_kmem_reve[CGRA_KMEM_SIZE] = {  0x0, 0xf00e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
    #else
    const uint32_t  cgra_imem_reve[CGRA_IMEM_SIZE] = {  0xa008000c, 0x90000, 0x0, 0x0, 0x4680000a, 0x0, 0x2a400001, 0x0, 0x0, 0x0, 0xa5080808, 0x0, 0x0, 0xc80000, 0xb0000, 0x90000, 0x0, 0x0, 0x0, 0x0, 0x6a2b0001, 0x27490000, 0x0, 0x0, 0x0, 0x62c00000, 0xc80000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4b90000, 0x0, 0x6a310001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2a28000c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa008000c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa5080804, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x90000, 0xa008000c, 0x0, 0x0, 0x0, 0x0, 0x6a090001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5a28000c, 0x0, 0x4b80000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4a29000c, 0x0, 0xa6080800, 0x0, 0x0, 0x43880006, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    static uint32_t cgra_kmem_reve[CGRA_KMEM_SIZE] = {  0x0, 0xf00d, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
    #endif

    static uint32_t	i_index_soft;
    static uint32_t	i_NumBits_soft;

    volatile static uint32_t	i_index_cgra    __attribute__((section(".cgra_vars"), aligned(4), used));
    volatile static uint32_t	i_NumBits_cgra  __attribute__((section(".cgra_vars"), aligned(4), used));
    volatile static uint32_t	o_ret_cgra      __attribute__((section(".cgra_vars"), aligned(4), used));

    static uint32_t	o_ret_soft;


    /****************************************************************************/
    /**                                                                        **/
    /*                           EXPORTED VARIABLES                             */
    /**                                                                        **/
    /****************************************************************************/

    extern kcom_kernel_t reve_kernel = {
        .kmem   = cgra_kmem_reve,
        .imem   = cgra_imem_reve,
        .col_n  = CGRA_N_COLS,
        .in_n   = IN_VAR_DEPTH,
        .out_n  = OUT_VAR_DEPTH,
        .config = config,
        .func   = software,
        .check  = check,
        .name   = "Reversebits",
    };

    /****************************************************************************/
    /**                                                                        **/
    /*                            LOCAL FUNCTIONS                               */
    /**                                                                        **/
    /****************************************************************************/

    void config()
    {
        i_index_soft = 325;//kcom_getRand() % (UINT_MAX - 1 - 0 + 1) + 0;
        i_index_cgra = i_index_soft;
        i_NumBits_soft = N_BITS;
        i_NumBits_cgra = i_NumBits_soft;
    }

    void software(void)
    {
        unsigned ret = reversebits( &i_index_soft, &i_NumBits_soft, &o_ret_soft );
    }

    uint32_t check(void)
    {
        uint32_t errors = 0;

    #if PRINT_CGRA_RESULTS
        PRINTF("------------------------------\n");
        for( uint8_t c = 0; c < CGRA_COLS; c ++)
        {
            for( uint8_t r = 0; r < OUT_VAR_DEPTH; r++ )
            {
                PRINTF("[%d][%d]:%08x\t\t",c,r,cgra_output[c][r]);
            }
            PRINTF("\n");
        }
    #endif //PRINT_CGRA_RESULTS


    #if PRINT_RESULTS
            PRINTF("\nCGRA\t\tSoft\n");
    #endif

        for( int i = 0; i < 1; i++ )
        {
    #if PRINT_RESULTS
            PRINTF("%08x\t%08x\t%s\n",
            o_ret_cgra,
            o_ret_soft,
            (o_ret_cgra != o_ret_soft) ? "Wrong!" : ""
            );
    #endif

            if (o_ret_cgra != o_ret_soft) {
                errors++;
            }
        }
        return errors;
    }

#endif
/****************************************************************************/
/**                                                                        **/
/**                                EOF                                     **/
/**                                                                        **/
/****************************************************************************/