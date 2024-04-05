/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "park.y"

#include <stdio.h>
#include <stdlib.h>
extern char *yytext;
int yyerror(char *s);
int yylex();
int yywrap();

#line 80 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    TYPE_IDENTIFIER = 259,         /* TYPE_IDENTIFIER  */
    FLOAT_CONSTANT = 260,          /* FLOAT_CONSTANT  */
    INTEGER_CONSTANT = 261,        /* INTEGER_CONSTANT  */
    CHARACTER_CONSTANT = 262,      /* CHARACTER_CONSTANT  */
    STRING_LITERAL = 263,          /* STRING_LITERAL  */
    PLUS = 264,                    /* PLUS  */
    MINUS = 265,                   /* MINUS  */
    PLUSPLUS = 266,                /* PLUSPLUS  */
    MINUSMINUS = 267,              /* MINUSMINUS  */
    BAR = 268,                     /* BAR  */
    AMP = 269,                     /* AMP  */
    BARBAR = 270,                  /* BARBAR  */
    AMPAMP = 271,                  /* AMPAMP  */
    ARROW = 272,                   /* ARROW  */
    SEMICOLON = 273,               /* SEMICOLON  */
    LSS = 274,                     /* LSS  */
    GTR = 275,                     /* GTR  */
    LEQ = 276,                     /* LEQ  */
    GEQ = 277,                     /* GEQ  */
    EQL = 278,                     /* EQL  */
    NEQ = 279,                     /* NEQ  */
    DOTDOTDOT = 280,               /* DOTDOTDOT  */
    LP = 281,                      /* LP  */
    RP = 282,                      /* RP  */
    LB = 283,                      /* LB  */
    RB = 284,                      /* RB  */
    LR = 285,                      /* LR  */
    RR = 286,                      /* RR  */
    PERIOD = 287,                  /* PERIOD  */
    COMMA = 288,                   /* COMMA  */
    EXCL = 289,                    /* EXCL  */
    STAR = 290,                    /* STAR  */
    SLASH = 291,                   /* SLASH  */
    PERCENT = 292,                 /* PERCENT  */
    ASSIGN = 293,                  /* ASSIGN  */
    COLON = 294,                   /* COLON  */
    AUTO_SYM = 295,                /* AUTO_SYM  */
    STATIC_SYM = 296,              /* STATIC_SYM  */
    TYPEDEF_SYM = 297,             /* TYPEDEF_SYM  */
    STRUCT_SYM = 298,              /* STRUCT_SYM  */
    ENUM_SYM = 299,                /* ENUM_SYM  */
    SIZEOF_SYM = 300,              /* SIZEOF_SYM  */
    UNION_SYM = 301,               /* UNION_SYM  */
    IF_SYM = 302,                  /* IF_SYM  */
    ELSE_SYM = 303,                /* ELSE_SYM  */
    WHILE_SYM = 304,               /* WHILE_SYM  */
    DO_SYM = 305,                  /* DO_SYM  */
    FOR_SYM = 306,                 /* FOR_SYM  */
    CONTINUE_SYM = 307,            /* CONTINUE_SYM  */
    BREAK_SYM = 308,               /* BREAK_SYM  */
    RETURN_SYM = 309,              /* RETURN_SYM  */
    SWITCH_SYM = 310,              /* SWITCH_SYM  */
    CASE_SYM = 311,                /* CASE_SYM  */
    DEFAULT_SYM = 312              /* DEFAULT_SYM  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IDENTIFIER 258
#define TYPE_IDENTIFIER 259
#define FLOAT_CONSTANT 260
#define INTEGER_CONSTANT 261
#define CHARACTER_CONSTANT 262
#define STRING_LITERAL 263
#define PLUS 264
#define MINUS 265
#define PLUSPLUS 266
#define MINUSMINUS 267
#define BAR 268
#define AMP 269
#define BARBAR 270
#define AMPAMP 271
#define ARROW 272
#define SEMICOLON 273
#define LSS 274
#define GTR 275
#define LEQ 276
#define GEQ 277
#define EQL 278
#define NEQ 279
#define DOTDOTDOT 280
#define LP 281
#define RP 282
#define LB 283
#define RB 284
#define LR 285
#define RR 286
#define PERIOD 287
#define COMMA 288
#define EXCL 289
#define STAR 290
#define SLASH 291
#define PERCENT 292
#define ASSIGN 293
#define COLON 294
#define AUTO_SYM 295
#define STATIC_SYM 296
#define TYPEDEF_SYM 297
#define STRUCT_SYM 298
#define ENUM_SYM 299
#define SIZEOF_SYM 300
#define UNION_SYM 301
#define IF_SYM 302
#define ELSE_SYM 303
#define WHILE_SYM 304
#define DO_SYM 305
#define FOR_SYM 306
#define CONTINUE_SYM 307
#define BREAK_SYM 308
#define RETURN_SYM 309
#define SWITCH_SYM 310
#define CASE_SYM 311
#define DEFAULT_SYM 312

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_TYPE_IDENTIFIER = 4,            /* TYPE_IDENTIFIER  */
  YYSYMBOL_FLOAT_CONSTANT = 5,             /* FLOAT_CONSTANT  */
  YYSYMBOL_INTEGER_CONSTANT = 6,           /* INTEGER_CONSTANT  */
  YYSYMBOL_CHARACTER_CONSTANT = 7,         /* CHARACTER_CONSTANT  */
  YYSYMBOL_STRING_LITERAL = 8,             /* STRING_LITERAL  */
  YYSYMBOL_PLUS = 9,                       /* PLUS  */
  YYSYMBOL_MINUS = 10,                     /* MINUS  */
  YYSYMBOL_PLUSPLUS = 11,                  /* PLUSPLUS  */
  YYSYMBOL_MINUSMINUS = 12,                /* MINUSMINUS  */
  YYSYMBOL_BAR = 13,                       /* BAR  */
  YYSYMBOL_AMP = 14,                       /* AMP  */
  YYSYMBOL_BARBAR = 15,                    /* BARBAR  */
  YYSYMBOL_AMPAMP = 16,                    /* AMPAMP  */
  YYSYMBOL_ARROW = 17,                     /* ARROW  */
  YYSYMBOL_SEMICOLON = 18,                 /* SEMICOLON  */
  YYSYMBOL_LSS = 19,                       /* LSS  */
  YYSYMBOL_GTR = 20,                       /* GTR  */
  YYSYMBOL_LEQ = 21,                       /* LEQ  */
  YYSYMBOL_GEQ = 22,                       /* GEQ  */
  YYSYMBOL_EQL = 23,                       /* EQL  */
  YYSYMBOL_NEQ = 24,                       /* NEQ  */
  YYSYMBOL_DOTDOTDOT = 25,                 /* DOTDOTDOT  */
  YYSYMBOL_LP = 26,                        /* LP  */
  YYSYMBOL_RP = 27,                        /* RP  */
  YYSYMBOL_LB = 28,                        /* LB  */
  YYSYMBOL_RB = 29,                        /* RB  */
  YYSYMBOL_LR = 30,                        /* LR  */
  YYSYMBOL_RR = 31,                        /* RR  */
  YYSYMBOL_PERIOD = 32,                    /* PERIOD  */
  YYSYMBOL_COMMA = 33,                     /* COMMA  */
  YYSYMBOL_EXCL = 34,                      /* EXCL  */
  YYSYMBOL_STAR = 35,                      /* STAR  */
  YYSYMBOL_SLASH = 36,                     /* SLASH  */
  YYSYMBOL_PERCENT = 37,                   /* PERCENT  */
  YYSYMBOL_ASSIGN = 38,                    /* ASSIGN  */
  YYSYMBOL_COLON = 39,                     /* COLON  */
  YYSYMBOL_AUTO_SYM = 40,                  /* AUTO_SYM  */
  YYSYMBOL_STATIC_SYM = 41,                /* STATIC_SYM  */
  YYSYMBOL_TYPEDEF_SYM = 42,               /* TYPEDEF_SYM  */
  YYSYMBOL_STRUCT_SYM = 43,                /* STRUCT_SYM  */
  YYSYMBOL_ENUM_SYM = 44,                  /* ENUM_SYM  */
  YYSYMBOL_SIZEOF_SYM = 45,                /* SIZEOF_SYM  */
  YYSYMBOL_UNION_SYM = 46,                 /* UNION_SYM  */
  YYSYMBOL_IF_SYM = 47,                    /* IF_SYM  */
  YYSYMBOL_ELSE_SYM = 48,                  /* ELSE_SYM  */
  YYSYMBOL_WHILE_SYM = 49,                 /* WHILE_SYM  */
  YYSYMBOL_DO_SYM = 50,                    /* DO_SYM  */
  YYSYMBOL_FOR_SYM = 51,                   /* FOR_SYM  */
  YYSYMBOL_CONTINUE_SYM = 52,              /* CONTINUE_SYM  */
  YYSYMBOL_BREAK_SYM = 53,                 /* BREAK_SYM  */
  YYSYMBOL_RETURN_SYM = 54,                /* RETURN_SYM  */
  YYSYMBOL_SWITCH_SYM = 55,                /* SWITCH_SYM  */
  YYSYMBOL_CASE_SYM = 56,                  /* CASE_SYM  */
  YYSYMBOL_DEFAULT_SYM = 57,               /* DEFAULT_SYM  */
  YYSYMBOL_YYACCEPT = 58,                  /* $accept  */
  YYSYMBOL_program = 59,                   /* program  */
  YYSYMBOL_translation_unit = 60,          /* translation_unit  */
  YYSYMBOL_external_declaration = 61,      /* external_declaration  */
  YYSYMBOL_function_definition = 62,       /* function_definition  */
  YYSYMBOL_declaration = 63,               /* declaration  */
  YYSYMBOL_declaration_specifiers = 64,    /* declaration_specifiers  */
  YYSYMBOL_storage_class_specifier = 65,   /* storage_class_specifier  */
  YYSYMBOL_init_declarator_list = 66,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 67,           /* init_declarator  */
  YYSYMBOL_type_specifier = 68,            /* type_specifier  */
  YYSYMBOL_struct_specifier = 69,          /* struct_specifier  */
  YYSYMBOL_struct_or_union = 70,           /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 71,   /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 72,        /* struct_declaration  */
  YYSYMBOL_struct_declarator_list = 73,    /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 74,         /* struct_declarator  */
  YYSYMBOL_enum_specifier = 75,            /* enum_specifier  */
  YYSYMBOL_enumerator_list = 76,           /* enumerator_list  */
  YYSYMBOL_enumerator = 77,                /* enumerator  */
  YYSYMBOL_declarator = 78,                /* declarator  */
  YYSYMBOL_pointer = 79,                   /* pointer  */
  YYSYMBOL_direct_declarator = 80,         /* direct_declarator  */
  YYSYMBOL_constant_expression_opt = 81,   /* constant_expression_opt  */
  YYSYMBOL_parameter_type_list_opt = 82,   /* parameter_type_list_opt  */
  YYSYMBOL_parameter_type_list = 83,       /* parameter_type_list  */
  YYSYMBOL_parameter_list = 84,            /* parameter_list  */
  YYSYMBOL_parameter_declaration = 85,     /* parameter_declaration  */
  YYSYMBOL_abstract_declarator_opt = 86,   /* abstract_declarator_opt  */
  YYSYMBOL_abstract_declarator = 87,       /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 88, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 89,               /* initializer  */
  YYSYMBOL_initializer_list = 90,          /* initializer_list  */
  YYSYMBOL_statement = 91,                 /* statement  */
  YYSYMBOL_labeled_statement = 92,         /* labeled_statement  */
  YYSYMBOL_compound_statement = 93,        /* compound_statement  */
  YYSYMBOL_declaration_list = 94,          /* declaration_list  */
  YYSYMBOL_statement_list = 95,            /* statement_list  */
  YYSYMBOL_expression_statement = 96,      /* expression_statement  */
  YYSYMBOL_selection_statement = 97,       /* selection_statement  */
  YYSYMBOL_iteration_statement = 98,       /* iteration_statement  */
  YYSYMBOL_expression_opt = 99,            /* expression_opt  */
  YYSYMBOL_jump_statement = 100,           /* jump_statement  */
  YYSYMBOL_primary_expression = 101,       /* primary_expression  */
  YYSYMBOL_postfix_expression = 102,       /* postfix_expression  */
  YYSYMBOL_arg_expression_list_opt = 103,  /* arg_expression_list_opt  */
  YYSYMBOL_arg_expression_list = 104,      /* arg_expression_list  */
  YYSYMBOL_unary_expression = 105,         /* unary_expression  */
  YYSYMBOL_cast_expression = 106,          /* cast_expression  */
  YYSYMBOL_type_name = 107,                /* type_name  */
  YYSYMBOL_multiplicative_expression = 108, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 109,      /* additive_expression  */
  YYSYMBOL_shift_expression = 110,         /* shift_expression  */
  YYSYMBOL_relational_expression = 111,    /* relational_expression  */
  YYSYMBOL_equality_expression = 112,      /* equality_expression  */
  YYSYMBOL_exclusive_OR_expression = 113,  /* exclusive_OR_expression  */
  YYSYMBOL_inclusive_OR_expression = 114,  /* inclusive_OR_expression  */
  YYSYMBOL_logical_AND_expression = 115,   /* logical_AND_expression  */
  YYSYMBOL_logical_OR_expression = 116,    /* logical_OR_expression  */
  YYSYMBOL_conditional_expression = 117,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 118,    /* assignment_expression  */
  YYSYMBOL_comma_expression = 119,         /* comma_expression  */
  YYSYMBOL_expression = 120,               /* expression  */
  YYSYMBOL_constant_expression = 121       /* constant_expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   510

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  64
/* YYNRULES -- Number of rules.  */
#define YYNRULES  160
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  279

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   312


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    23,    23,    27,    28,    32,    33,    37,    38,    42,
      43,    47,    48,    50,    51,    56,    57,    58,    62,    63,
      67,    68,    72,    73,    74,    78,    79,    80,    83,    84,
      88,    89,    93,   104,   105,   109,   115,   116,   117,   121,
     122,   126,   127,   148,   149,   153,   154,   160,   161,   162,
     163,   167,   168,   172,   173,   177,   178,   182,   183,   187,
     188,   192,   193,   197,   198,   199,   203,   204,   205,   206,
     207,   211,   212,   216,   217,   221,   222,   223,   224,   225,
     226,   230,   231,   232,   236,   240,   241,   245,   246,   250,
     251,   255,   256,   257,   261,   262,   263,   267,   268,   272,
     273,   274,   279,   280,   281,   282,   283,   284,   287,   288,
     289,   290,   291,   292,   293,   297,   298,   302,   303,   307,
     308,   309,   310,   311,   312,   314,   315,   316,   317,   321,
     322,   325,   326,   329,   330,   331,   332,   336,   337,   338,
     342,   347,   348,   349,   350,   351,   355,   356,   357,   366,
     372,   377,   378,   382,   383,   387,   392,   393,   397,   402,
     406
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "TYPE_IDENTIFIER", "FLOAT_CONSTANT", "INTEGER_CONSTANT",
  "CHARACTER_CONSTANT", "STRING_LITERAL", "PLUS", "MINUS", "PLUSPLUS",
  "MINUSMINUS", "BAR", "AMP", "BARBAR", "AMPAMP", "ARROW", "SEMICOLON",
  "LSS", "GTR", "LEQ", "GEQ", "EQL", "NEQ", "DOTDOTDOT", "LP", "RP", "LB",
  "RB", "LR", "RR", "PERIOD", "COMMA", "EXCL", "STAR", "SLASH", "PERCENT",
  "ASSIGN", "COLON", "AUTO_SYM", "STATIC_SYM", "TYPEDEF_SYM", "STRUCT_SYM",
  "ENUM_SYM", "SIZEOF_SYM", "UNION_SYM", "IF_SYM", "ELSE_SYM", "WHILE_SYM",
  "DO_SYM", "FOR_SYM", "CONTINUE_SYM", "BREAK_SYM", "RETURN_SYM",
  "SWITCH_SYM", "CASE_SYM", "DEFAULT_SYM", "$accept", "program",
  "translation_unit", "external_declaration", "function_definition",
  "declaration", "declaration_specifiers", "storage_class_specifier",
  "init_declarator_list", "init_declarator", "type_specifier",
  "struct_specifier", "struct_or_union", "struct_declaration_list",
  "struct_declaration", "struct_declarator_list", "struct_declarator",
  "enum_specifier", "enumerator_list", "enumerator", "declarator",
  "pointer", "direct_declarator", "constant_expression_opt",
  "parameter_type_list_opt", "parameter_type_list", "parameter_list",
  "parameter_declaration", "abstract_declarator_opt",
  "abstract_declarator", "direct_abstract_declarator", "initializer",
  "initializer_list", "statement", "labeled_statement",
  "compound_statement", "declaration_list", "statement_list",
  "expression_statement", "selection_statement", "iteration_statement",
  "expression_opt", "jump_statement", "primary_expression",
  "postfix_expression", "arg_expression_list_opt", "arg_expression_list",
  "unary_expression", "cast_expression", "type_name",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression",
  "exclusive_OR_expression", "inclusive_OR_expression",
  "logical_AND_expression", "logical_OR_expression",
  "conditional_expression", "assignment_expression", "comma_expression",
  "expression", "constant_expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-211)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     164,  -211,  -211,   122,    -5,  -211,  -211,  -211,  -211,    25,
    -211,    46,   164,  -211,  -211,  -211,    97,   143,   143,  -211,
      32,  -211,    60,    23,    10,    24,  -211,    69,    73,  -211,
    -211,  -211,     9,  -211,     7,  -211,  -211,    96,    63,  -211,
    -211,    10,   143,   411,  -211,    73,   105,    71,  -211,  -211,
     122,   398,  -211,    63,   122,    35,  -211,   143,    94,   108,
    -211,   128,  -211,  -211,  -211,  -211,  -211,  -211,   411,   411,
     452,   452,   411,   335,   411,   411,   465,   137,  -211,   148,
     139,  -211,    57,    59,  -211,   132,    87,  -211,  -211,   159,
     163,  -211,  -211,  -211,    88,   411,  -211,    73,  -211,   144,
     398,  -211,  -211,    43,    11,  -211,  -211,  -211,  -211,  -211,
      97,   225,   356,   411,  -211,    22,  -211,  -211,    15,  -211,
     259,  -211,  -211,  -211,   411,  -211,  -211,  -211,     5,   154,
    -211,  -211,   161,  -211,  -211,   335,  -211,  -211,  -211,  -211,
     188,   411,   411,   191,   411,   411,   411,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,  -211,  -211,
    -211,  -211,   100,  -211,  -211,   122,   157,  -211,  -211,   171,
     172,   280,   174,   183,   211,   411,   212,   411,   170,  -211,
    -211,  -211,  -211,  -211,  -211,  -211,   222,   214,   215,   216,
      15,   143,   411,  -211,  -211,   322,   136,  -211,   411,  -211,
     217,  -211,   219,   220,  -211,   218,  -211,  -211,  -211,  -211,
    -211,    57,    57,  -211,  -211,  -211,  -211,   132,   132,  -211,
     159,  -211,   398,  -211,   280,   411,   411,   199,   411,  -211,
    -211,   231,  -211,   411,   213,   280,  -211,  -211,  -211,  -211,
     223,   228,  -211,  -211,  -211,   411,  -211,  -211,  -211,   227,
     234,   232,   244,  -211,   237,   280,  -211,  -211,  -211,  -211,
     280,   280,   411,   411,   280,  -211,   221,  -211,   238,   248,
    -211,   280,   249,   411,  -211,  -211,   246,   280,  -211
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    47,    24,     0,    46,    15,    16,    17,    28,     0,
      29,     0,     2,     3,     5,     6,     0,    12,    11,    22,
       0,    23,     0,     0,    44,     0,    45,    38,     0,     1,
       4,     9,     0,    18,    20,    14,    13,    27,     0,    85,
       8,    43,    53,    51,    48,     0,    41,     0,    39,    10,
       0,     0,     7,     0,     0,     0,    30,    87,    61,     0,
      54,    55,    57,   102,   104,   103,   105,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   108,   119,
     129,   133,   137,   140,   141,   146,   149,   150,   151,   153,
     155,   156,   160,    52,     0,     0,    37,     0,    19,    20,
       0,    21,    71,     0,     0,    33,    35,    26,    31,    86,
       0,     0,    53,    51,    59,    63,    60,    62,    64,    50,
       0,   129,   125,   126,     0,   120,   121,   122,   131,     0,
     158,   159,     0,   124,   123,     0,   127,    49,   113,   114,
       0,   115,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,    42,
      40,    73,     0,    25,    32,     0,   102,    89,    84,     0,
       0,     0,     0,     0,     0,    97,     0,    51,     0,    88,
      75,    76,    77,    78,    79,    80,     0,     0,     0,     0,
      65,    53,    51,    56,    58,    53,    63,   132,     0,   107,
       0,   112,     0,   116,   117,     0,   111,   157,   134,   135,
     136,   138,   139,   142,   143,   144,   145,   147,   148,   152,
     154,    72,     0,    34,     0,     0,     0,     0,    97,   100,
     101,     0,    98,     0,     0,     0,    90,    68,    66,    67,
       0,     0,   130,   128,   110,     0,   109,    74,    83,     0,
       0,     0,     0,    99,     0,     0,    82,    70,    69,   118,
       0,     0,     0,    97,     0,    81,    91,    94,     0,     0,
      93,     0,     0,    97,    92,    95,     0,     0,    96
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -211,  -211,  -211,   281,  -211,   239,     2,  -211,  -211,   245,
     -21,  -211,  -211,   251,   -32,  -211,   106,  -211,   252,   210,
       6,     0,   -12,   -97,   -41,  -211,  -211,   189,  -211,   -37,
    -100,   -95,  -211,  -147,  -211,    39,  -211,  -211,  -211,  -211,
    -211,  -210,  -211,  -211,  -211,  -211,  -211,    70,   -62,   173,
      21,  -211,    61,    18,  -211,  -211,   155,   156,  -211,  -211,
     -43,  -211,   -70,   224
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    11,    12,    13,    14,    15,    58,    17,    32,    33,
      18,    19,    20,    55,    56,   104,   105,    21,    47,    48,
      22,    23,    24,    77,   187,    60,    61,    62,   116,   188,
     118,   101,   162,   179,   180,   181,    57,   111,   182,   183,
     184,   231,   185,    78,    79,   202,   203,    80,    81,   129,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
     130,   131,   186,    93
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      92,    59,    16,   132,    26,   161,   122,   123,   102,    25,
     127,    41,   133,   134,    16,   190,   189,    54,   252,    35,
      36,   117,    34,   108,   227,     1,     1,    49,    27,   164,
       4,   195,    54,   113,    54,    37,    42,    39,    43,     2,
       4,   191,    50,   192,   165,    51,    29,     2,   112,     3,
     113,    44,    92,   269,   132,    28,    99,   102,   115,   110,
     106,    40,    38,   276,   114,   132,   107,     2,   148,   149,
      92,   108,   205,    52,   163,   128,    46,   248,     8,     9,
     234,    10,    54,   208,   209,   210,     8,     9,   256,    10,
      39,   197,   145,   146,   147,   241,   190,     1,   204,    45,
       1,   207,    96,    41,    97,   232,     8,     9,   265,    10,
     154,   155,   115,   266,   267,    31,    99,   270,    25,   158,
     112,    97,   113,     3,   274,     1,    53,   247,   196,     4,
     278,   221,     4,   222,    92,   119,   242,   128,   121,   121,
     125,   126,   121,    95,   121,   121,   136,     2,     3,    92,
     240,   150,   151,   152,   153,   249,   250,     4,   232,   138,
     139,   120,   195,   254,   113,   140,   137,     1,     2,   211,
     212,   106,   217,   218,   141,   156,   142,   144,   157,   102,
     143,   198,    51,     5,     6,     7,     8,     9,   199,    10,
       3,   201,   268,   232,   206,   196,   224,   225,   226,     4,
     228,   229,   259,   232,     5,     6,     7,     8,     9,   235,
      10,   213,   214,   215,   216,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   166,   230,
      64,    65,    66,    67,    68,    69,    70,    71,   233,    72,
     236,   237,   238,   167,   243,   239,   244,   246,   251,   253,
     257,    73,   255,   245,   260,    39,   168,   258,   262,    74,
      75,   261,   263,     2,   264,   272,   273,   275,   121,   271,
      76,   223,   169,   277,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   166,   193,    64,    65,    66,    67,    68,
      69,    70,    71,    30,    72,    98,   109,    94,   167,     5,
       6,     7,     8,     9,   103,    10,    73,   160,   200,   194,
      39,   219,     0,   220,    74,    75,     0,     0,     0,   159,
       0,     0,     0,     0,     0,    76,     2,   169,     0,   170,
     171,   172,   173,   174,   175,   176,   177,   178,    63,     2,
      64,    65,    66,    67,    68,    69,    70,    71,   195,    72,
     113,     0,     0,     0,     0,     0,     0,     4,     0,     1,
       2,    73,     5,     6,     7,     8,     9,     0,    10,    74,
      75,     0,     0,     0,     0,     5,     6,     7,     8,     9,
      76,    10,   112,     0,   113,     0,     0,     0,     0,     0,
       0,     4,     0,     0,     0,     0,     5,     6,     7,     8,
       9,    63,    10,    64,    65,    66,    67,    68,    69,    70,
      71,     0,    72,     0,    63,     0,    64,    65,    66,    67,
      68,    69,    70,    71,    73,    72,     0,     0,   100,     0,
       0,     0,    74,    75,     0,     0,     0,    73,     0,     0,
       0,     0,     0,    76,     0,    74,    75,     0,     0,     0,
       0,     0,     0,     0,     0,    63,    76,    64,    65,    66,
      67,    68,    69,    70,    71,     0,    72,     0,    63,     0,
      64,    65,    66,    67,    68,    69,    70,    71,   124,    72,
       0,     0,     0,     0,     0,     0,    74,    75,     0,     0,
       0,   135,     0,     0,     0,     0,     0,    76,     0,    74,
      75,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      76
};

static const yytype_int16 yycheck[] =
{
      43,    42,     0,    73,     4,   100,    68,    69,    51,     3,
      72,    23,    74,    75,    12,   115,   113,    38,   228,    17,
      18,    58,    16,    55,   171,     3,     3,    18,     3,    18,
      35,    26,    53,    28,    55,     3,    26,    30,    28,     4,
      35,    26,    33,    28,    33,    38,     0,     4,    26,    26,
      28,    27,    95,   263,   124,    30,    50,   100,    58,    57,
      54,    22,    30,   273,    58,   135,    31,     4,     9,    10,
     113,   103,   142,    34,    31,    73,     3,   224,    43,    44,
     177,    46,   103,   145,   146,   147,    43,    44,   235,    46,
      30,   128,    35,    36,    37,   192,   196,     3,   141,    30,
       3,   144,    31,   115,    33,   175,    43,    44,   255,    46,
      23,    24,   112,   260,   261,    18,   110,   264,   112,    31,
      26,    33,    28,    26,   271,     3,    30,   222,   128,    35,
     277,    31,    35,    33,   177,    27,   198,   135,    68,    69,
      70,    71,    72,    38,    74,    75,    76,     4,    26,   192,
     191,    19,    20,    21,    22,   225,   226,    35,   228,    11,
      12,    33,    26,   233,    28,    17,    29,     3,     4,   148,
     149,   165,   154,   155,    26,    16,    28,    38,    15,   222,
      32,    27,    38,    40,    41,    42,    43,    44,    27,    46,
      26,     3,   262,   263,     3,   195,    39,    26,    26,    35,
      26,    18,   245,   273,    40,    41,    42,    43,    44,    39,
      46,   150,   151,   152,   153,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,     3,    18,
       5,     6,     7,     8,     9,    10,    11,    12,    26,    14,
      18,    27,    27,    18,    27,    29,    27,    29,    49,    18,
      27,    26,    39,    33,    27,    30,    31,    29,    26,    34,
      35,    27,    18,     4,    27,    27,    18,    18,   198,    48,
      45,   165,    47,    27,    49,    50,    51,    52,    53,    54,
      55,    56,    57,     3,    25,     5,     6,     7,     8,     9,
      10,    11,    12,    12,    14,    50,    57,    45,    18,    40,
      41,    42,    43,    44,    53,    46,    26,    97,   135,   120,
      30,   156,    -1,   157,    34,    35,    -1,    -1,    -1,    95,
      -1,    -1,    -1,    -1,    -1,    45,     4,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    26,    14,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,     3,
       4,    26,    40,    41,    42,    43,    44,    -1,    46,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      45,    46,    26,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      44,     3,    46,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    14,    -1,     3,    -1,     5,     6,     7,     8,
       9,    10,    11,    12,    26,    14,    -1,    -1,    30,    -1,
      -1,    -1,    34,    35,    -1,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    45,     5,     6,     7,
       8,     9,    10,    11,    12,    -1,    14,    -1,     3,    -1,
       5,     6,     7,     8,     9,    10,    11,    12,    26,    14,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    -1,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    45,    -1,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,    26,    35,    40,    41,    42,    43,    44,
      46,    59,    60,    61,    62,    63,    64,    65,    68,    69,
      70,    75,    78,    79,    80,    78,    79,     3,    30,     0,
      61,    18,    66,    67,    78,    64,    64,     3,    30,    30,
      93,    80,    26,    28,    27,    30,     3,    76,    77,    18,
      33,    38,    93,    30,    68,    71,    72,    94,    64,    82,
      83,    84,    85,     3,     5,     6,     7,     8,     9,    10,
      11,    12,    14,    26,    34,    35,    45,    81,   101,   102,
     105,   106,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   121,    76,    38,    31,    33,    67,    78,
      30,    89,   118,    71,    73,    74,    78,    31,    72,    63,
      64,    95,    26,    28,    78,    79,    86,    87,    88,    27,
      33,   105,   106,   106,    26,   105,   105,   106,    64,   107,
     118,   119,   120,   106,   106,    26,   105,    29,    11,    12,
      17,    26,    28,    32,    38,    35,    36,    37,     9,    10,
      19,    20,    21,    22,    23,    24,    16,    15,    31,   121,
      77,    89,    90,    31,    18,    33,     3,    18,    31,    47,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    91,
      92,    93,    96,    97,    98,   100,   120,    82,    87,    81,
      88,    26,    28,    25,    85,    26,    79,    87,    27,    27,
     107,     3,   103,   104,   118,   120,     3,   118,   106,   106,
     106,   108,   108,   110,   110,   110,   110,   111,   111,   114,
     115,    31,    33,    74,    39,    26,    26,    91,    26,    18,
      18,    99,   120,    26,    81,    39,    18,    27,    27,    29,
      82,    81,   106,    27,    27,    33,    29,    89,    91,   120,
     120,    49,    99,    18,   120,    39,    91,    27,    29,   118,
      27,    27,    26,    18,    27,    91,    91,    91,   120,    99,
      91,    48,    27,    18,    91,    18,    99,    27,    91
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    58,    59,    60,    60,    61,    61,    62,    62,    63,
      63,    64,    64,    64,    64,    65,    65,    65,    66,    66,
      67,    67,    68,    68,    68,    69,    69,    69,    70,    70,
      71,    71,    72,    73,    73,    74,    75,    75,    75,    76,
      76,    77,    77,    78,    78,    79,    79,    80,    80,    80,
      80,    81,    81,    82,    82,    83,    83,    84,    84,    85,
      85,    86,    86,    87,    87,    87,    88,    88,    88,    88,
      88,    89,    89,    90,    90,    91,    91,    91,    91,    91,
      91,    92,    92,    92,    93,    94,    94,    95,    95,    96,
      96,    97,    97,    97,    98,    98,    98,    99,    99,   100,
     100,   100,   101,   101,   101,   101,   101,   101,   102,   102,
     102,   102,   102,   102,   102,   103,   103,   104,   104,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   106,
     106,   107,   107,   108,   108,   108,   108,   109,   109,   109,
     110,   111,   111,   111,   111,   111,   112,   112,   112,   113,
     114,   115,   115,   116,   116,   117,   118,   118,   119,   120,
     121
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     2,     2,
       3,     1,     1,     2,     2,     1,     1,     1,     1,     3,
       1,     3,     1,     1,     1,     5,     4,     2,     1,     1,
       1,     2,     3,     1,     3,     1,     5,     4,     2,     1,
       3,     1,     3,     2,     1,     2,     1,     1,     3,     4,
       4,     0,     1,     0,     1,     1,     3,     1,     3,     2,
       2,     0,     1,     1,     1,     2,     3,     3,     3,     4,
       4,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     4,     3,     3,     4,     0,     2,     0,     2,     1,
       2,     5,     7,     5,     5,     7,     9,     0,     1,     3,
       2,     2,     1,     1,     1,     1,     1,     3,     1,     4,
       4,     3,     3,     2,     2,     0,     1,     1,     3,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     4,     1,
       4,     1,     2,     1,     3,     3,     3,     1,     3,     3,
       1,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       1,     1,     3,     1,     3,     1,     1,     3,     1,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {

#line 1605 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 409 "park.y"


extern char *yytext;

int main(int argc, char **argv) {
    yyparse();
    printf("Success\n");
}

int yyerror(char *s) {
    fprintf(stderr, "%s near %s\n", s, yytext);
    exit(1);
}

int yywrap() {
    return (1);
}
