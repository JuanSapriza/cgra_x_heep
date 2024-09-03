/*
                              *******************
******************************* C SOURCE FILE *******************************
**                            *******************                          **
**                                                                         **
** project  : CGRA-X-HEEP                                                  **
** filename : sha.c                                                 **
** version  : 1                                                            **
** date     : 2023-06-27                                                       **
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
* @file   sha.c
* @date   2023-06-27
* @brief  A description of the kernel...
*
*/

#define _SHA_C

#define N_ITERS 80

/****************************************************************************/
/**                                                                        **/
/*                             MODULES USED                                 */
/**                                                                        **/
/****************************************************************************/
#include <stdint.h>

#include "sha.h"
#include "function.h"

/****************************************************************************/
/**                                                                        **/
/*                        DEFINITIONS AND MACROS                            */
/**                                                                        **/
/****************************************************************************/

#if CGRA_N_COLS == 2
    #define CGRA_COLS       2
    #define IN_VAR_DEPTH    4
    #define OUT_VAR_DEPTH   2

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

    const uint32_t  cgra_imem_sha[CGRA_IMEM_SIZE] = {  0xa90000, 0x0, 0x0, 0x0, 0x2a180004, 0x62080000, 0x62080000, 0x0, 0x24500000, 0x14500000, 0x13c00000, 0x2a180004, 0x62080000, 0x62080000, 0x0, 0x24500000, 0x14500000, 0x13c00000, 0xc80000, 0xa90000, 0xab0000, 0x0, 0x4a081ffd, 0x4a180004, 0x4a180004, 0x3b80000, 0x14500000, 0x47800010, 0x64080000, 0x4a081ffd, 0x4a180004, 0x4a180004, 0x3b80000, 0x14500000, 0x47880009, 0x64080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xab0000, 0x0, 0x0, 0x2a081ff0, 0x0, 0x75080000, 0x72090000, 0x5b80000, 0x6b80000, 0x0, 0x2a081ff0, 0x0, 0x75080000, 0x72090000, 0x5b80000, 0x6b80000, 0x0, 0x0, 0x0, 0xa090010, 0x0, 0x600b0000, 0x7a081ff8, 0x7a081ff2, 0x3a180004, 0x3b80000, 0x7a090001, 0x7a180004, 0x600b0000, 0x7a081ff8, 0x7a081ff2, 0x3a180004, 0x3b80000, 0x7a090001, 0x7a180004, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  };
    static uint32_t cgra_kmem_sha[CGRA_KMEM_SIZE] = {  0x0, 0x3012, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    };

    static int32_t cgra_input[CGRA_COLS][IN_VAR_DEPTH]     __attribute__ ((aligned (4)));
    static int32_t cgra_output[CGRA_COLS][OUT_VAR_DEPTH]   __attribute__ ((aligned (4)));

    static uint32_t	i_w_soft[80];
    static uint32_t	i_w_cgra[80];

    static uint32_t	*o_ret_soft;
    static uint32_t	*o_ret_cgra;


    /****************************************************************************/
    /**                                                                        **/
    /*                           EXPORTED VARIABLES                             */
    /**                                                                        **/
    /****************************************************************************/

    extern kcom_kernel_t sha_kernel = {
        .kmem   = cgra_kmem_sha,
        .imem   = cgra_imem_sha,
        .col_n  = CGRA_COLS,
        .in_n   = IN_VAR_DEPTH,
        .out_n  = OUT_VAR_DEPTH,
        .input  = cgra_input,
        .output = cgra_output,
        .config = config,
        .func   = software,
        .check  = check,
        .name   = "Sha",
    };

    /****************************************************************************/
    /**                                                                        **/
    /*                            LOCAL FUNCTIONS                               */
    /**                                                                        **/
    /****************************************************************************/

    void config()
    {
        for(int i = 0; i < 80; i++ )
        {
            i_w_soft[i] = kcom_getRand() % (UINT_MAX - 1 - 0 + 1) + 0;
            i_w_cgra[i] = i_w_soft[i];
        }
        cgra_input[0][0] = i_w_cgra;
        cgra_input[1][0] = i_w_cgra;
        cgra_input[0][1] = i_w_cgra;
        cgra_input[1][1] = 80;

    }

    void software(void)
    {
        o_ret_soft = sha_transform( i_w_soft );
    }

    uint32_t check(void)
    {
        uint32_t errors = 0;

        o_ret_cgra = i_w_cgra;


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

        for( int i = 0; i < 80; i++ )
        {
    #if PRINT_RESULTS
            PRINTF("%08x\t%08x\t%s\n",
            o_ret_cgra[i],
            o_ret_soft[i],
            (o_ret_cgra[i] != o_ret_soft[i]) ? "Wrong!" : ""
            );
    #endif

            if (o_ret_cgra[i] != o_ret_soft[i]) {
                errors++;
            }
        }
        PRINTF("%d",errors);
        return errors;
    }

#elif CGRA_N_COLS == 3

    #define CGRA_COLS       3
    #define IN_VAR_DEPTH    3
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

    const uint32_t  cgra_imem_sha[CGRA_IMEM_SIZE] = {  0x0, 0x0, 0x2a081ff8, 0x2a180004, 0x0, 0x0, 0x2a081ff8, 0x2a180004, 0x0, 0x43c00000, 0x2a081ff8, 0x2a180004, 0x0, 0x43c00000, 0x0, 0x0, 0x0, 0x43c00000, 0xc80000, 0xa90000, 0x0, 0x0, 0x0, 0x0, 0x62080000, 0x0, 0x0, 0x0, 0x62080000, 0x0, 0x0, 0x0, 0x62080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa080010, 0x10080000, 0x0, 0x1a080001, 0x0, 0x10080000, 0x0, 0x1a080001, 0x0, 0x10080000, 0x0, 0x1a080001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0x0, 0x0, 0x4a180004, 0x61080000, 0x1b80000, 0x15500000, 0x4a180004, 0x61080000, 0x1b80000, 0x15500000, 0x4a180004, 0x61080000, 0x1b80000, 0x15500000, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0x0, 0x0, 0x3a180004, 0x3a180004, 0x0, 0x61080000, 0x3a180004, 0x3a180004, 0x0, 0x61080000, 0x3a180004, 0x3a180004, 0x0, 0x61080000, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0x0, 0x4a081ffd, 0x4a081ff0, 0x4680000d, 0x0, 0x4a081ffd, 0x4a081ff0, 0x4680000d, 0x0, 0x4a081ffd, 0x4a081ff0, 0x46880009, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3b80000, 0x2b80000, 0x41500000, 0x13500000, 0x3b80000, 0x2b80000, 0x41500000, 0x13500000, 0x3b80000, 0x2b80000, 0x41500000, 0x13500000, 0x0, 0x0, 0xa90000, 0x0, 0x0, 0x0, 0x64080000, 0x0, 0x0, 0x4b80000, 0x64080000, 0x0, 0x0, 0x4b80000, 0x64080000, 0x0, 0x0, 0x4b80000, 0x0, 0x0, 0x0, 0xa90000, 0x0, 0x5a081ff2, 0x1a180004, 0x0, 0x61080000, 0x5a081ff2, 0x1a180004, 0x0, 0x61080000, 0x5a081ff2, 0x1a180004, 0x0, 0x61080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  };
    static uint32_t cgra_kmem_sha[CGRA_KMEM_SIZE] = {  0x0, 0x7012, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, };

    static int32_t cgra_input[CGRA_COLS][IN_VAR_DEPTH]     __attribute__ ((aligned (4)));
    static int32_t cgra_output[CGRA_COLS][OUT_VAR_DEPTH]   __attribute__ ((aligned (4)));

    static uint32_t	i_w_soft[N_ITERS];
    static uint32_t	i_w_cgra[N_ITERS];

    static uint32_t	*o_ret_soft;
    static uint32_t	*o_ret_cgra;


    /****************************************************************************/
    /**                                                                        **/
    /*                           EXPORTED VARIABLES                             */
    /**                                                                        **/
    /****************************************************************************/

    extern kcom_kernel_t sha_kernel = {
        .kmem   = cgra_kmem_sha,
        .imem   = cgra_imem_sha,
        .col_n  = CGRA_COLS,
        .in_n   = IN_VAR_DEPTH,
        .out_n  = OUT_VAR_DEPTH,
        .input  = cgra_input,
        .output = cgra_output,
        .config = config,
        .func   = software,
        .check  = check,
        .name   = "Sha",
    };

    /****************************************************************************/
    /**                                                                        **/
    /*                            LOCAL FUNCTIONS                               */
    /**                                                                        **/
    /****************************************************************************/

    void config()
    {

        for(int i = 0; i < N_ITERS; i++ )
        {
            i_w_soft[i] = kcom_getRand() % (UINT_MAX - 1 - 0 + 1) + 0;
            i_w_cgra[i] = i_w_soft[i];
        }
        cgra_input[0][0] = i_w_cgra;

        cgra_input[1][0] = i_w_cgra;
        cgra_input[1][1] = i_w_cgra;
        cgra_input[1][2] = i_w_cgra;

        cgra_input[2][0] = N_ITERS;
        cgra_input[2][1] = i_w_cgra;
    }

    void software(void)
    {
        o_ret_soft = sha_transform( i_w_soft  );
    }

    uint32_t check(void)
    {
        uint32_t errors = 0;

        o_ret_cgra = i_w_cgra;


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

        for( int i = 14; i < N_ITERS; i++ )
        {
    #if PRINT_RESULTS
            PRINTF("%08x\t%08x\t%s\n",
            o_ret_cgra[i],
            o_ret_soft[i],
            ( o_ret_cgra[i] != o_ret_soft[i] ) ? "Wrong!" : ""
            );
    #endif

            if (o_ret_cgra[i] != o_ret_soft[i]) {
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
    const uint32_t  cgra_imem_sha[CGRA_IMEM_SIZE] = { 0xa009000c, 0x6a29000c, 0xa6090800, 0x0, 0x4a081ff8, 0x0, 0x0, 0x4a081ff8, 0x65080000, 0x52500000, 0x4a081ff8, 0x65080000, 0x52500000, 0x0, 0x65080000, 0x52500000, 0x0, 0x0, 0x0, 0x0, 0x65080000, 0x52500000, 0x0, 0x0, 0xc80000, 0xc80000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2a180004, 0x0, 0x0, 0x2a180004, 0x2b80000, 0x21500000, 0x2a180004, 0x2b80000, 0x21500000, 0x0, 0x2b80000, 0x21500000, 0xa0a00018, 0x0, 0x0, 0x0, 0x2b80000, 0x21500000, 0x0, 0x0, 0x0, 0xa009000c, 0x6a28000c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x24c00000, 0x0, 0x0, 0x24c00000, 0x0, 0x0, 0x24c00000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x24c00000, 0x0, 0x0, 0xa009000c, 0x6a29000c, 0xa6080800, 0x0, 0x0, 0x0, 0x4a180004, 0x61080000, 0x1b80000, 0x4a180004, 0x61080000, 0x1b80000, 0x4a180004, 0x61080000, 0x1b80000, 0x0, 0x0, 0x0, 0x4a180004, 0x61080000, 0x1b80000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa009000c, 0x6a28000c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5a180004, 0x32500000, 0x0, 0x5a180004, 0x32500000, 0x0, 0x5a180004, 0x32500000, 0x0, 0x0, 0x0, 0x0, 0x5a180004, 0x32500000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa2090800, 0x0, 0x0, 0x0, 0x64080000, 0x1b80000, 0x0, 0x64080000, 0x1b80000, 0x0, 0x64080000, 0x1b80000, 0x0, 0x0, 0x0, 0x0, 0x64080000, 0x1b80000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa5090800, 0x0, 0x0, 0x0, 0x65080000, 0x1b80000, 0x0, 0x65080000, 0x1b80000, 0x0, 0x65080000, 0x1b80000, 0x0, 0x0, 0x0, 0x0, 0x65080000, 0x1b80000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa080010, 0x0, 0x0, 0x5a080001, 0x0, 0x5a081ff0, 0x5a080001, 0x0, 0x5a081ff0, 0x5a080001, 0x0, 0x5a081ff0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5a081ff0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa090050, 0x0, 0x0, 0x0, 0x26800012, 0x0, 0x0, 0x2680000c, 0x0, 0x0, 0x26880009, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa009000c, 0x6a28000c, 0x0, 0x0, 0x0, 0x5a180004, 0x0, 0x0, 0x5a180004, 0x0, 0x0, 0x5a180004, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40080000, 0x0, 0x0, 0x40080000, 0x0, 0x0, 0x40080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2a180004, 0x0, 0x0, 0x2a180004, 0x0, 0x0, 0x2a180004, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa5090800, 0x0, 0x0, 0x0, 0x0, 0x0, 0x62080000, 0x0, 0x0, 0x62080000, 0x0, 0x0, 0x62080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x62080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3a081ffd, 0x3a081ff2, 0x0, 0x3a081ffd, 0x3a081ff2, 0x0, 0x3a081ffd, 0x3a081ff2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  };
    static uint32_t cgra_kmem_sha[CGRA_KMEM_SIZE] = {  0x0,  0xf019,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0 };
    #else
    const uint32_t  cgra_imem_sha[CGRA_IMEM_SIZE] = { 0xa008000c, 0x0, 0xa4090800, 0x0, 0x0, 0x65080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc80000, 0xc80000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5a180004, 0x0, 0x4b80000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5a180004, 0x0, 0x0, 0x0, 0x0, 0x32500000, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa5090800, 0x0, 0x0, 0x620b0000, 0x3b80000, 0x4bd0000, 0x48500000, 0x0, 0x27c00000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2a180004, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3a081ff8, 0x0, 0x3a081ff0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa090010, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6a090001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5a28000c, 0x0, 0x2a081ffd, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa008000c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2a28000c, 0x0, 0x0, 0x4a180004, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa008000c, 0x5a28000c, 0xa090050, 0x4a081ff2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46880003, 0x0, 0x0, 0xa008000c, 0x0, 0x0, 0x0, 0x2a180004, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5a28000c, 0x0, 0x0, 0x0, 0x0, 0x3b80000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa4090800, 0x0, 0x0, 0x34080000, 0x0, 0x65080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa008000c, 0x4a28000c, 0xa4080800, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa2090800, 0x0, 0x0, 0x0, 0x64080000, 0x35500000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  };
    static uint32_t cgra_kmem_sha[CGRA_KMEM_SIZE] = {  0x0,  0xf00c,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0 };
    #endif

    volatile static int32_t	i_W_cgra[80] __attribute__((section(".cgra_vars"), aligned(4), used ));

    static int32_t	i_W_soft[80];


    /****************************************************************************/
    /**                                                                        **/
    /*                           EXPORTED VARIABLES                             */
    /**                                                                        **/
    /****************************************************************************/

    extern kcom_kernel_t sha_kernel = {
        .kmem   = cgra_kmem_sha,
        .imem   = cgra_imem_sha,
        .col_n  = CGRA_COLS,
        .in_n   = 2,
        .out_n  = 1,
        .config = config,
        .func   = software,
        .check  = check,
        .name   = "Sha",
    };

    /****************************************************************************/
    /**                                                                        **/
    /*                            LOCAL FUNCTIONS                               */
    /**                                                                        **/
    /****************************************************************************/

    void config()
    {
        for(int i = 0; i < 80; i++ )
        {
            i_W_soft[i] = kcom_getRand() % (UINT_MAX - 1 - 0 + 1) + 0;
            i_W_cgra[i] = i_W_soft[i];
        }
    }

    void software(void)
    {
        sha_transform( i_W_soft );
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

        for( int i = 0; i < 80; i++ )
        {
    #if PRINT_RESULTS
            PRINTF("%08x\t%08x\t%s\n",
            i_W_cgra[i],
            i_W_soft[i],
            (i_W_cgra[i] != i_W_soft[i]) ? "Wrong!" : ""
            );
    #endif

            if (i_W_cgra[i] != i_W_soft[i]) {
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