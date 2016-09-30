/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         WASM_AST_PARSER_STYPE
#define YYLTYPE         WASM_AST_PARSER_LTYPE
/* Substitute the variable and function names.  */
#define yyparse         wasm_ast_parser_parse
#define yylex           wasm_ast_parser_lex
#define yyerror         wasm_ast_parser_error
#define yydebug         wasm_ast_parser_debug
#define yynerrs         wasm_ast_parser_nerrs


/* Copy the first part of user declarations.  */
#line 17 "src/wasm-ast-parser.y" /* yacc.c:339  */

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "wasm-allocator.h"
#include "wasm-ast-parser.h"
#include "wasm-ast-parser-lexer-shared.h"
#include "wasm-binary-reader-ast.h"
#include "wasm-binary-reader.h"
#include "wasm-literal.h"

/* the default value for YYMAXDEPTH is 10000, which can be easily hit since our
   grammar is right-recursive.

   we can increase YYMAXDEPTH, but the generated parser says that "results are
   undefined" if YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES(YYMAXDEPTH) with
   infinite-precision arithmetic. That's tricky to write a static assertion
   for, so let's "just" limit YYSTACK_BYTES(YYMAXDEPTH) to UINT32_MAX and use
   64-bit arithmetic. this static assert is done at the end of the file, so all
   defines are available. */
#define YYMAXDEPTH 10000000

#define DUPTEXT(dst, src)                                                   \
  (dst).start = wasm_strndup(parser->allocator, (src).start, (src).length); \
  (dst).length = (src).length

#define YYLLOC_DEFAULT(Current, Rhs, N)                       \
  do                                                          \
    if (N) {                                                  \
      (Current).filename = YYRHSLOC(Rhs, 1).filename;         \
      (Current).line = YYRHSLOC(Rhs, 1).line;                 \
      (Current).first_column = YYRHSLOC(Rhs, 1).first_column; \
      (Current).last_column = YYRHSLOC(Rhs, N).last_column;   \
    } else {                                                  \
      (Current).filename = NULL;                              \
      (Current).line = YYRHSLOC(Rhs, 0).line;                 \
      (Current).first_column = (Current).last_column =        \
          YYRHSLOC(Rhs, 0).last_column;                       \
    }                                                         \
  while (0)

#define APPEND_FIELD_TO_LIST(module, field, KIND, kind, loc_, item) \
  do {                                                              \
    field = wasm_append_module_field(parser->allocator, module);    \
    field->loc = loc_;                                              \
    field->type = WASM_MODULE_FIELD_TYPE_##KIND;                    \
    field->kind = item;                                             \
  } while (0)

#define APPEND_ITEM_TO_VECTOR(module, Kind, kind, kinds, item_ptr)      \
  do {                                                                  \
    Wasm##Kind* dummy = item_ptr;                                       \
    wasm_append_##kind##_ptr_value(parser->allocator, &(module)->kinds, \
                                   &dummy);                             \
  } while (0)

#define INSERT_BINDING(module, kind, kinds, loc_, name)            \
  do                                                               \
    if ((name).start) {                                            \
      WasmBinding* binding = wasm_insert_binding(                  \
          parser->allocator, &(module)->kind##_bindings, &(name)); \
      binding->loc = loc_;                                         \
      binding->index = (module)->kinds.size - 1;                   \
    }                                                              \
  while (0)

#define APPEND_INLINE_EXPORT(module, KIND, loc_, value, index_)         \
  do                                                                    \
    if ((value).export_.has_export) {                                   \
      WasmModuleField* export_field;                                    \
      APPEND_FIELD_TO_LIST(module, export_field, EXPORT, export_, loc_, \
                           (value).export_.export_);                    \
      export_field->export_.kind = WASM_EXTERNAL_KIND_##KIND;           \
      export_field->export_.var.index = index_;                         \
      APPEND_ITEM_TO_VECTOR(module, Export, export, exports,            \
                            &export_field->export_);                    \
      INSERT_BINDING(module, export, exports, export_field->loc,        \
                     export_field->export_.name);                       \
    }                                                                   \
  while (0)

#define CHECK_IMPORT_ORDERING(module, kind, kinds, loc_)               \
  do {                                                                 \
    if ((module)->kinds.size != (module)->num_##kind##_imports) {      \
      wasm_ast_parser_error(&loc_, lexer, parser,                      \
                            "imported " #kind                          \
                            " must occur before all defined " #kinds); \
    }                                                                  \
  } while (0)

#define YYMALLOC(size) wasm_alloc(parser->allocator, size, WASM_DEFAULT_ALIGN)
#define YYFREE(p) wasm_free(parser->allocator, p)

#define USE_NATURAL_ALIGNMENT (~0)

static WasmExprList join_exprs1(WasmLocation* loc, WasmExpr* expr1);
static WasmExprList join_exprs2(WasmLocation* loc, WasmExprList* expr1,
                                WasmExpr* expr2);

static WasmFuncField* new_func_field(WasmAllocator* allocator) {
  return wasm_alloc_zero(allocator, sizeof(WasmFuncField), WASM_DEFAULT_ALIGN);
}

static WasmFunc* new_func(WasmAllocator* allocator) {
  return wasm_alloc_zero(allocator, sizeof(WasmFunc), WASM_DEFAULT_ALIGN);
}

static WasmCommand* new_command(WasmAllocator* allocator) {
  return wasm_alloc_zero(allocator, sizeof(WasmCommand), WASM_DEFAULT_ALIGN);
}

static WasmModule* new_module(WasmAllocator* allocator) {
  return wasm_alloc_zero(allocator, sizeof(WasmModule), WASM_DEFAULT_ALIGN);
}

static WasmImport* new_import(WasmAllocator* allocator) {
  return wasm_alloc_zero(allocator, sizeof(WasmImport), WASM_DEFAULT_ALIGN);
}

static WasmTextListNode* new_text_list_node(WasmAllocator* allocator) {
  return wasm_alloc_zero(allocator, sizeof(WasmTextListNode),
                         WASM_DEFAULT_ALIGN);
}

static WasmResult parse_const(WasmType type, WasmLiteralType literal_type,
                              const char* s, const char* end, WasmConst* out);
static void dup_text_list(WasmAllocator*, WasmTextList* text_list,
                          void** out_data, size_t* out_size);

static WasmBool is_empty_signature(WasmFuncSignature* sig);

static void append_implicit_func_declaration(WasmAllocator*, WasmLocation*,
                                             WasmModule*, WasmFuncDeclaration*);

typedef struct BinaryErrorCallbackData {
  WasmLocation* loc;
  WasmAstLexer* lexer;
  WasmAstParser* parser;
} BinaryErrorCallbackData;

static void on_read_binary_error(uint32_t offset, const char* error,
                                 void* user_data);

#define wasm_ast_parser_lex wasm_ast_lexer_lex


#line 223 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "wasm-ast-parser-gen.h".  */
#ifndef YY_WASM_AST_PARSER_SRC_PREBUILT_WASM_AST_PARSER_GEN_H_INCLUDED
# define YY_WASM_AST_PARSER_SRC_PREBUILT_WASM_AST_PARSER_GEN_H_INCLUDED
/* Debug traces.  */
#ifndef WASM_AST_PARSER_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define WASM_AST_PARSER_DEBUG 1
#  else
#   define WASM_AST_PARSER_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define WASM_AST_PARSER_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined WASM_AST_PARSER_DEBUG */
#if WASM_AST_PARSER_DEBUG
extern int wasm_ast_parser_debug;
#endif

/* Token type.  */
#ifndef WASM_AST_PARSER_TOKENTYPE
# define WASM_AST_PARSER_TOKENTYPE
  enum wasm_ast_parser_tokentype
  {
    WASM_TOKEN_TYPE_EOF = 0,
    WASM_TOKEN_TYPE_LPAR = 258,
    WASM_TOKEN_TYPE_RPAR = 259,
    WASM_TOKEN_TYPE_NAT = 260,
    WASM_TOKEN_TYPE_INT = 261,
    WASM_TOKEN_TYPE_FLOAT = 262,
    WASM_TOKEN_TYPE_TEXT = 263,
    WASM_TOKEN_TYPE_VAR = 264,
    WASM_TOKEN_TYPE_VALUE_TYPE = 265,
    WASM_TOKEN_TYPE_ANYFUNC = 266,
    WASM_TOKEN_TYPE_MUT = 267,
    WASM_TOKEN_TYPE_NOP = 268,
    WASM_TOKEN_TYPE_DROP = 269,
    WASM_TOKEN_TYPE_BLOCK = 270,
    WASM_TOKEN_TYPE_END = 271,
    WASM_TOKEN_TYPE_IF = 272,
    WASM_TOKEN_TYPE_THEN = 273,
    WASM_TOKEN_TYPE_ELSE = 274,
    WASM_TOKEN_TYPE_LOOP = 275,
    WASM_TOKEN_TYPE_BR = 276,
    WASM_TOKEN_TYPE_BR_IF = 277,
    WASM_TOKEN_TYPE_BR_TABLE = 278,
    WASM_TOKEN_TYPE_CALL = 279,
    WASM_TOKEN_TYPE_CALL_IMPORT = 280,
    WASM_TOKEN_TYPE_CALL_INDIRECT = 281,
    WASM_TOKEN_TYPE_RETURN = 282,
    WASM_TOKEN_TYPE_GET_LOCAL = 283,
    WASM_TOKEN_TYPE_SET_LOCAL = 284,
    WASM_TOKEN_TYPE_TEE_LOCAL = 285,
    WASM_TOKEN_TYPE_GET_GLOBAL = 286,
    WASM_TOKEN_TYPE_SET_GLOBAL = 287,
    WASM_TOKEN_TYPE_LOAD = 288,
    WASM_TOKEN_TYPE_STORE = 289,
    WASM_TOKEN_TYPE_OFFSET_EQ_NAT = 290,
    WASM_TOKEN_TYPE_ALIGN_EQ_NAT = 291,
    WASM_TOKEN_TYPE_CONST = 292,
    WASM_TOKEN_TYPE_UNARY = 293,
    WASM_TOKEN_TYPE_BINARY = 294,
    WASM_TOKEN_TYPE_COMPARE = 295,
    WASM_TOKEN_TYPE_CONVERT = 296,
    WASM_TOKEN_TYPE_SELECT = 297,
    WASM_TOKEN_TYPE_UNREACHABLE = 298,
    WASM_TOKEN_TYPE_CURRENT_MEMORY = 299,
    WASM_TOKEN_TYPE_GROW_MEMORY = 300,
    WASM_TOKEN_TYPE_FUNC = 301,
    WASM_TOKEN_TYPE_START = 302,
    WASM_TOKEN_TYPE_TYPE = 303,
    WASM_TOKEN_TYPE_PARAM = 304,
    WASM_TOKEN_TYPE_RESULT = 305,
    WASM_TOKEN_TYPE_LOCAL = 306,
    WASM_TOKEN_TYPE_GLOBAL = 307,
    WASM_TOKEN_TYPE_MODULE = 308,
    WASM_TOKEN_TYPE_TABLE = 309,
    WASM_TOKEN_TYPE_ELEM = 310,
    WASM_TOKEN_TYPE_MEMORY = 311,
    WASM_TOKEN_TYPE_DATA = 312,
    WASM_TOKEN_TYPE_OFFSET = 313,
    WASM_TOKEN_TYPE_IMPORT = 314,
    WASM_TOKEN_TYPE_EXPORT = 315,
    WASM_TOKEN_TYPE_REGISTER = 316,
    WASM_TOKEN_TYPE_INVOKE = 317,
    WASM_TOKEN_TYPE_GET = 318,
    WASM_TOKEN_TYPE_ASSERT_MALFORMED = 319,
    WASM_TOKEN_TYPE_ASSERT_INVALID = 320,
    WASM_TOKEN_TYPE_ASSERT_UNLINKABLE = 321,
    WASM_TOKEN_TYPE_ASSERT_RETURN = 322,
    WASM_TOKEN_TYPE_ASSERT_RETURN_NAN = 323,
    WASM_TOKEN_TYPE_ASSERT_TRAP = 324,
    WASM_TOKEN_TYPE_INPUT = 325,
    WASM_TOKEN_TYPE_OUTPUT = 326,
    WASM_TOKEN_TYPE_LOW = 327
  };
#endif

/* Value type.  */
#if ! defined WASM_AST_PARSER_STYPE && ! defined WASM_AST_PARSER_STYPE_IS_DECLARED
typedef WasmToken WASM_AST_PARSER_STYPE;
# define WASM_AST_PARSER_STYPE_IS_TRIVIAL 1
# define WASM_AST_PARSER_STYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined WASM_AST_PARSER_LTYPE && ! defined WASM_AST_PARSER_LTYPE_IS_DECLARED
typedef struct WASM_AST_PARSER_LTYPE WASM_AST_PARSER_LTYPE;
struct WASM_AST_PARSER_LTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define WASM_AST_PARSER_LTYPE_IS_DECLARED 1
# define WASM_AST_PARSER_LTYPE_IS_TRIVIAL 1
#endif



int wasm_ast_parser_parse (WasmAstLexer* lexer, WasmAstParser* parser);

#endif /* !YY_WASM_AST_PARSER_SRC_PREBUILT_WASM_AST_PARSER_GEN_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 369 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined WASM_AST_PARSER_LTYPE_IS_TRIVIAL && WASM_AST_PARSER_LTYPE_IS_TRIVIAL \
             && defined WASM_AST_PARSER_STYPE_IS_TRIVIAL && WASM_AST_PARSER_STYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   750

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  169
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  389

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   327

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72
};

#if WASM_AST_PARSER_DEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   276,   276,   282,   292,   293,   297,   315,   316,   322,
     325,   330,   337,   340,   341,   345,   350,   357,   360,   363,
     368,   375,   381,   392,   396,   400,   407,   412,   419,   420,
     426,   427,   430,   434,   435,   439,   440,   450,   451,   462,
     463,   464,   467,   470,   473,   476,   479,   483,   487,   492,
     495,   499,   503,   507,   511,   515,   519,   523,   529,   535,
     547,   551,   555,   559,   563,   566,   571,   576,   581,   586,
     594,   602,   606,   609,   615,   621,   630,   636,   641,   647,
     652,   658,   666,   667,   675,   676,   684,   689,   690,   696,
     702,   712,   718,   724,   734,   789,   798,   805,   812,   822,
     825,   829,   834,   843,   849,   869,   875,   885,   892,   913,
     936,   943,   956,   963,   969,   975,   981,   989,   994,  1001,
    1007,  1013,  1019,  1028,  1036,  1041,  1046,  1051,  1058,  1065,
    1069,  1072,  1083,  1087,  1094,  1098,  1101,  1109,  1117,  1134,
    1150,  1161,  1168,  1175,  1181,  1221,  1231,  1253,  1263,  1288,
    1289,  1293,  1301,  1311,  1317,  1323,  1329,  1335,  1340,  1349,
    1354,  1355,  1361,  1369,  1370,  1378,  1390,  1391,  1398,  1407
};
#endif

#if WASM_AST_PARSER_DEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"EOF\"", "error", "$undefined", "\"(\"", "\")\"", "NAT", "INT",
  "FLOAT", "TEXT", "VAR", "VALUE_TYPE", "ANYFUNC", "MUT", "NOP", "DROP",
  "BLOCK", "END", "IF", "THEN", "ELSE", "LOOP", "BR", "BR_IF", "BR_TABLE",
  "CALL", "CALL_IMPORT", "CALL_INDIRECT", "RETURN", "GET_LOCAL",
  "SET_LOCAL", "TEE_LOCAL", "GET_GLOBAL", "SET_GLOBAL", "LOAD", "STORE",
  "OFFSET_EQ_NAT", "ALIGN_EQ_NAT", "CONST", "UNARY", "BINARY", "COMPARE",
  "CONVERT", "SELECT", "UNREACHABLE", "CURRENT_MEMORY", "GROW_MEMORY",
  "FUNC", "START", "TYPE", "PARAM", "RESULT", "LOCAL", "GLOBAL", "MODULE",
  "TABLE", "ELEM", "MEMORY", "DATA", "OFFSET", "IMPORT", "EXPORT",
  "REGISTER", "INVOKE", "GET", "ASSERT_MALFORMED", "ASSERT_INVALID",
  "ASSERT_UNLINKABLE", "ASSERT_RETURN", "ASSERT_RETURN_NAN", "ASSERT_TRAP",
  "INPUT", "OUTPUT", "LOW", "$accept", "non_empty_text_list", "text_list",
  "quoted_text", "value_type_list", "elem_type", "global_type",
  "func_type", "func_sig", "table_sig", "memory_sig", "limits", "type_use",
  "nat", "literal", "var", "var_list", "bind_var_opt", "bind_var",
  "labeling_opt", "offset_opt", "align_opt", "instr", "plain_instr",
  "block_instr", "block", "expr", "expr1", "if_", "instr_list",
  "expr_list", "const_expr", "func_fields", "func_body", "func_info",
  "func", "offset", "elem", "table", "data", "memory", "global",
  "import_kind", "import", "inline_import", "export_kind", "export",
  "inline_export_opt", "inline_export", "type_def", "start",
  "module_fields", "raw_module", "module", "script_var_opt", "action",
  "assertion", "cmd", "cmd_list", "const", "const_list", "script",
  "script_start", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327
};
# endif

#define YYPACT_NINF -289

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-289)))

#define YYTABLE_NINF -30

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -289,    73,  -289,    93,    80,  -289,  -289,  -289,  -289,  -289,
    -289,    94,    97,    94,    94,   109,   109,   109,   125,   125,
     125,  -289,   158,  -289,    94,    97,    97,    85,    97,    97,
      97,    -1,  -289,   122,    97,  -289,    67,    82,   177,  -289,
     187,   203,   206,   219,   191,  -289,   220,  -289,  -289,   117,
    -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,
    -289,  -289,   209,  -289,  -289,  -289,  -289,   196,  -289,  -289,
    -289,   226,   118,    39,   226,   226,    99,   226,    99,    97,
      97,  -289,   224,  -289,   361,  -289,  -289,  -289,  -289,   232,
     199,   242,   245,    33,   246,   282,   249,  -289,  -289,   256,
     249,   158,    97,   257,  -289,  -289,  -289,   262,   241,  -289,
    -289,   226,   226,   226,   118,   118,  -289,   118,   118,  -289,
     118,   118,   118,   118,   118,   252,   252,   224,  -289,  -289,
    -289,  -289,  -289,  -289,  -289,  -289,   394,   427,  -289,  -289,
    -289,  -289,  -289,  -289,   273,   285,   460,  -289,   290,  -289,
     294,    23,  -289,   427,    44,    44,   157,   289,    59,  -289,
     226,   226,   226,   427,   304,   331,  -289,   146,   123,   289,
     289,   315,   158,   309,   332,   334,   133,   335,  -289,   118,
     226,  -289,   226,    97,    97,  -289,  -289,  -289,  -289,  -289,
    -289,   118,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,
     308,   308,  -289,   565,   342,   705,  -289,  -289,   194,   343,
     349,   526,   394,   359,   171,   373,  -289,   369,  -289,   376,
     374,   392,   427,   406,   401,   289,  -289,   410,   415,  -289,
    -289,  -289,   425,   304,  -289,  -289,   197,  -289,  -289,   158,
     439,  -289,   441,   389,   448,  -289,   144,   458,   118,   118,
     118,   118,  -289,   472,   103,   468,   148,   149,   469,    97,
     481,   328,   479,   151,   495,   130,  -289,  -289,  -289,  -289,
    -289,  -289,  -289,  -289,   505,  -289,  -289,   508,  -289,  -289,
     514,  -289,  -289,  -289,   473,  -289,  -289,    53,  -289,  -289,
    -289,  -289,   525,  -289,  -289,   158,  -289,   226,   226,   226,
     226,  -289,   538,   540,   541,   547,  -289,   394,  -289,   557,
     493,   493,   558,   568,  -289,  -289,  -289,  -289,   427,  -289,
     150,   174,  -289,  -289,  -289,  -289,   639,   570,  -289,   577,
     579,   285,    44,   289,   289,  -289,  -289,  -289,  -289,  -289,
     394,   604,  -289,  -289,   493,  -289,   574,   581,  -289,   200,
     427,   672,   304,  -289,   596,   597,   607,   608,   609,   616,
    -289,  -289,  -289,   572,   619,   625,   427,  -289,  -289,  -289,
    -289,  -289,  -289,  -289,  -289,  -289,   636,   646,   189,   621,
     648,  -289,   427,   645,   654,   427,  -289,   670,  -289
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     163,   168,   169,     0,     0,   148,   161,   159,   160,   164,
       1,   149,     0,   149,   149,     0,     0,     0,     0,     0,
       0,   150,   135,     6,   149,     0,     0,     0,     0,     0,
       0,     0,   166,     0,     0,     2,     0,     0,     0,   166,
       0,     0,     0,     0,     0,   157,     0,   147,     3,     0,
     146,   140,   141,   138,   142,   139,   137,   144,   145,   136,
     143,   162,     0,   152,   153,   154,   155,     0,   156,   167,
     158,    30,     0,     0,    30,    30,     0,    30,     0,     0,
       0,   151,     0,    32,    82,    31,    22,    27,    26,     0,
       0,     0,     0,     0,   129,     0,     0,   100,    28,   129,
       0,     4,     0,     0,    23,    24,    25,     0,     0,    43,
      44,    33,    33,    33,     0,     0,    28,     0,     0,    49,
       0,     0,     0,     0,     0,    35,    35,     0,    60,    61,
      62,    63,    45,    42,    64,    65,    82,    82,    39,    40,
      41,    91,    94,    87,     0,    13,    82,   134,    13,   132,
       0,     0,    10,    82,     0,     0,     0,     0,     0,   130,
      33,    33,    33,    82,    84,     0,    28,     0,     0,     0,
       0,   130,     4,     5,     0,     0,     0,     0,   165,     0,
       7,     7,     7,     0,     0,    34,     7,     7,     7,    46,
      47,     0,    50,    51,    52,    53,    54,    55,    56,    36,
      37,    37,    59,     0,     0,     0,    83,    98,     0,     0,
       0,     0,    82,     0,     0,     0,   133,     0,    86,     0,
       0,     0,    82,     0,     0,    19,     9,     0,     0,     7,
       7,     7,     0,    84,    72,    71,     0,   102,    29,     4,
       0,    18,     0,     0,     0,   106,     0,     0,     0,     0,
       0,     0,   128,     0,     0,     0,     0,     0,     0,     0,
       0,    82,     0,     0,     0,    48,    38,    57,    58,    96,
       7,     7,   119,   118,     0,    97,    12,     0,   111,   122,
       0,   120,    17,    20,     0,   103,    73,     0,    74,    99,
      85,   101,     0,   121,   107,     4,   105,    30,    30,    30,
      30,   117,     0,     0,     0,     0,    21,    82,     8,     0,
      82,    82,     0,     0,   131,    70,    66,    68,    82,    67,
       0,     0,    95,    11,   110,    28,     0,     0,    75,     0,
       0,    13,     0,     0,     0,   124,   127,   125,   126,    89,
      82,     0,    88,    92,    82,   123,     0,    14,    16,     0,
      82,     0,    81,   109,     0,     0,     0,     0,     0,     0,
      90,    93,    69,     0,     0,     0,    82,    80,   108,   113,
     112,   116,   114,   115,     7,   104,    77,     0,     0,     0,
      79,    15,    82,     0,     0,    82,    76,     0,    78
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -289,   653,  -155,   -22,  -152,   464,  -129,   599,  -139,  -145,
    -159,  -137,  -123,  -119,   580,   -23,  -106,   -59,   -46,   -40,
     571,   507,  -289,   -94,  -289,  -142,   -76,  -289,  -289,  -132,
     488,  -126,  -288,  -270,  -102,  -289,   -19,  -289,  -289,  -289,
    -289,  -289,  -289,  -289,    31,  -289,  -289,   624,    38,  -289,
    -289,  -289,   313,  -289,    55,   314,  -289,  -289,  -289,  -289,
     685,  -289,  -289
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   173,   174,    24,   261,   227,   153,    91,   209,   223,
     240,   224,   136,    88,   107,   238,   167,    84,    85,   186,
     200,   267,   137,   138,   139,   262,   140,   165,   328,   141,
     234,   219,   142,   143,   144,    51,    98,    52,    53,    54,
      55,    56,   247,    57,   145,   177,    58,   158,   146,    59,
      60,    37,     5,     6,    22,     7,     8,     9,     1,    69,
      44,     2,     3
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      97,   164,    97,    39,    40,   206,    41,    42,    43,   215,
     191,   242,    46,   228,   164,    93,    94,   244,    99,   339,
      97,   218,   210,   212,    97,   221,   222,    92,   254,   256,
     257,   218,   241,   241,   204,   217,   151,   232,   225,   225,
     342,   343,    90,   152,   213,   263,   264,   220,    83,    89,
     225,   225,   360,    96,   152,   100,   326,   102,   103,   101,
     236,    13,    14,   308,    86,   185,   185,   185,    25,    26,
     226,    47,   187,   188,   361,    48,     4,   166,   287,    38,
     175,   172,   183,   184,   292,    49,    50,   286,   233,   288,
     218,   189,   190,    10,   192,   193,   280,   194,   195,   196,
     197,   198,    95,    21,    86,    23,   283,   307,    87,   164,
     274,   164,    27,   308,   185,   185,   185,   164,   320,   321,
     229,   230,   231,    86,   154,   157,    45,    87,    31,   315,
     169,   155,   159,    11,   255,   -29,   258,   171,    11,   -29,
     330,    12,    13,    14,    15,    16,    17,    18,    19,    20,
     237,    86,   310,   311,   347,    87,   253,   233,   308,   308,
     308,   259,   260,    71,    72,    73,    35,   317,   265,    74,
     318,    75,    76,    77,    78,   359,    79,    80,   348,   248,
     239,    61,   183,   184,   308,   249,   346,   250,   358,   251,
     297,    63,   355,   381,    67,    68,   298,   241,   299,   308,
     300,   291,    86,   357,   364,    86,    87,    64,   356,    87,
      65,   327,    67,    81,   225,   225,   183,   184,   365,   349,
     270,   271,   378,    66,    70,   302,   303,   304,   305,   104,
     105,   106,   164,    82,   377,    83,   147,   313,   331,   332,
     333,   334,   179,   270,   271,   148,   149,   164,    90,   156,
     384,   352,    95,   387,   109,   110,   160,   164,   161,   168,
     176,   162,   114,   115,   116,   117,   178,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   367,   207,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   199,   208,   179,
     180,   181,   182,   214,    86,   109,   110,   160,   216,   161,
     183,   184,   162,   114,   115,   116,   117,   205,   118,   119,
     120,   121,   122,   123,   124,   125,   126,    48,   243,   127,
     128,   129,   130,   131,   132,   133,   134,   135,    28,    29,
      30,   205,    32,    33,    34,   235,   245,   246,   308,   252,
     163,   109,   110,   111,   266,   112,   269,   272,   113,   114,
     115,   116,   117,   273,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   275,   108,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   109,   110,   111,   276,   112,   277,
     278,   113,   114,   115,   116,   117,   217,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   279,   203,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   109,   110,   111,
     281,   112,   226,   284,   113,   114,   115,   116,   117,   285,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   289,
     205,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     109,   110,   111,   293,   112,   294,   295,   113,   114,   115,
     116,   117,   296,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   301,   211,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   109,   110,   111,   306,   112,   309,   312,
     113,   114,   115,   116,   117,   314,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   316,   341,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   109,   110,   111,   322,
     112,   319,   323,   113,   114,   115,   116,   117,   324,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   325,   329,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   109,
     110,   160,   335,   161,   336,   337,   162,   114,   115,   116,
     117,   338,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   340,   344,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   345,   351,   179,   180,   181,   182,   109,   110,
     160,   353,   161,   354,   363,   162,   114,   115,   116,   117,
     362,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     368,   369,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   370,   371,   372,   180,   181,   182,   109,   110,   160,
     373,   161,   374,   375,   162,   114,   115,   116,   117,   376,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   379,
     382,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     380,   383,   109,   110,   160,   182,   161,   350,   386,   162,
     114,   115,   116,   117,   385,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   388,    36,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   109,   110,   160,   282,   161,
     366,   150,   162,   114,   115,   116,   117,   201,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   202,   268,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   109,   110,
     160,   290,   161,   170,    62,   162,   114,   115,   116,   117,
       0,   118,   119,   120,   121,   122,   123,   124,   125,   126,
       0,     0,   127,   128,   129,   130,   131,   132,   133,   134,
     135
};

static const yytype_int16 yycheck[] =
{
      76,    95,    78,    25,    26,   137,    28,    29,    30,   148,
     116,   170,    34,   158,   108,    74,    75,   172,    77,   307,
      96,   153,   145,   146,   100,   154,   155,    73,   180,   181,
     182,   163,   169,   170,   136,    12,     3,   163,   157,   158,
     310,   311,     3,    10,   146,   187,   188,     3,     9,    72,
     169,   170,   340,    76,    10,    78,     3,    79,    80,    78,
     166,    62,    63,    10,     5,   111,   112,   113,    13,    14,
      11,     4,   112,   113,   344,     8,     3,    96,   230,    24,
     102,   100,    59,    60,   239,     3,     4,   229,   164,   231,
     222,   114,   115,     0,   117,   118,   222,   120,   121,   122,
     123,   124,     3,     9,     5,     8,   225,     4,     9,   203,
     212,   205,     3,    10,   160,   161,   162,   211,   270,   271,
     160,   161,   162,     5,    93,    94,     4,     9,     3,   261,
      99,    93,    94,    53,   180,     5,   182,    99,    53,     9,
     295,    61,    62,    63,    64,    65,    66,    67,    68,    69,
       4,     5,     4,     4,     4,     9,   179,   233,    10,    10,
      10,   183,   184,    46,    47,    48,     8,    16,   191,    52,
      19,    54,    55,    56,    57,   334,    59,    60,     4,    46,
      57,     4,    59,    60,    10,    52,   318,    54,   333,    56,
      46,     4,   331,     4,     3,     4,    52,   334,    54,    10,
      56,     4,     5,   332,     4,     5,     9,     4,   331,     9,
       4,   287,     3,     4,   333,   334,    59,    60,   350,   325,
      49,    50,   374,     4,     4,   248,   249,   250,   251,     5,
       6,     7,   326,    37,   366,     9,     4,   259,   297,   298,
     299,   300,    48,    49,    50,    46,     4,   341,     3,     3,
     382,   327,     3,   385,    13,    14,    15,   351,    17,     3,
       3,    20,    21,    22,    23,    24,     4,    26,    27,    28,
      29,    30,    31,    32,    33,    34,   352,     4,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    35,     3,    48,
      49,    50,    51,     3,     5,    13,    14,    15,     4,    17,
      59,    60,    20,    21,    22,    23,    24,     3,    26,    27,
      28,    29,    30,    31,    32,    33,    34,     8,     3,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    15,    16,
      17,     3,    18,    19,    20,     4,     4,     3,    10,     4,
      58,    13,    14,    15,    36,    17,     4,     4,    20,    21,
      22,    23,    24,     4,    26,    27,    28,    29,    30,    31,
      32,    33,    34,     4,     3,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    13,    14,    15,     4,    17,    10,
       4,    20,    21,    22,    23,    24,    12,    26,    27,    28,
      29,    30,    31,    32,    33,    34,     4,     3,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    13,    14,    15,
       4,    17,    11,     3,    20,    21,    22,    23,    24,     4,
      26,    27,    28,    29,    30,    31,    32,    33,    34,     4,
       3,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      13,    14,    15,     4,    17,     4,    57,    20,    21,    22,
      23,    24,     4,    26,    27,    28,    29,    30,    31,    32,
      33,    34,     4,     3,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    13,    14,    15,     4,    17,    10,    10,
      20,    21,    22,    23,    24,     4,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    16,     3,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    13,    14,    15,     4,
      17,    16,     4,    20,    21,    22,    23,    24,     4,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    55,     4,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    13,
      14,    15,     4,    17,     4,     4,    20,    21,    22,    23,
      24,     4,    26,    27,    28,    29,    30,    31,    32,    33,
      34,     4,     4,    37,    38,    39,    40,    41,    42,    43,
      44,    45,     4,     3,    48,    49,    50,    51,    13,    14,
      15,     4,    17,     4,     3,    20,    21,    22,    23,    24,
      16,    26,    27,    28,    29,    30,    31,    32,    33,    34,
       4,     4,    37,    38,    39,    40,    41,    42,    43,    44,
      45,     4,     4,     4,    49,    50,    51,    13,    14,    15,
       4,    17,    50,     4,    20,    21,    22,    23,    24,     4,
      26,    27,    28,    29,    30,    31,    32,    33,    34,     3,
      19,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       4,     3,    13,    14,    15,    51,    17,    18,     4,    20,
      21,    22,    23,    24,    19,    26,    27,    28,    29,    30,
      31,    32,    33,    34,     4,    22,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    13,    14,    15,   224,    17,
      18,    92,    20,    21,    22,    23,    24,   126,    26,    27,
      28,    29,    30,    31,    32,    33,    34,   127,   201,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    13,    14,
      15,   233,    17,    99,    39,    20,    21,    22,    23,    24,
      -1,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   131,   134,   135,     3,   125,   126,   128,   129,   130,
       0,    53,    61,    62,    63,    64,    65,    66,    67,    68,
      69,     9,   127,     8,    76,   127,   127,     3,   125,   125,
     125,     3,   128,   128,   128,     8,    74,   124,   127,    76,
      76,    76,    76,    76,   133,     4,    76,     4,     8,     3,
       4,   108,   110,   111,   112,   113,   114,   116,   119,   122,
     123,     4,   133,     4,     4,     4,     4,     3,     4,   132,
       4,    46,    47,    48,    52,    54,    55,    56,    57,    59,
      60,     4,    37,     9,    90,    91,     5,     9,    86,    88,
       3,    80,    91,    90,    90,     3,    88,    99,   109,    90,
      88,   109,    76,    76,     5,     6,     7,    87,     3,    13,
      14,    15,    17,    20,    21,    22,    23,    24,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    85,    95,    96,    97,
      99,   102,   105,   106,   107,   117,   121,     4,    46,     4,
      80,     3,    10,    79,   117,   121,     3,   117,   120,   121,
      15,    17,    20,    58,    96,   100,   109,    89,     3,   117,
     120,   121,   109,    74,    75,    76,     3,   118,     4,    48,
      49,    50,    51,    59,    60,    91,    92,    92,    92,    88,
      88,    89,    88,    88,    88,    88,    88,    88,    88,    35,
      93,    93,    87,     3,   107,     3,   102,     4,     3,    81,
      85,     3,    85,   107,     3,    81,     4,    12,   102,   104,
       3,    79,    79,    82,    84,    86,    11,    78,    82,    92,
      92,    92,   104,    99,   103,     4,    89,     4,    88,    57,
      83,    84,    83,     3,    75,     4,     3,   115,    46,    52,
      54,    56,     4,    88,    77,    91,    77,    77,    91,    76,
      76,    77,    98,    98,    98,    88,    36,    94,    94,     4,
      49,    50,     4,     4,   107,     4,     4,    10,     4,     4,
     104,     4,    78,    86,     3,     4,    98,    77,    98,     4,
     103,     4,    75,     4,     4,    57,     4,    46,    52,    54,
      56,     4,    88,    88,    88,    88,     4,     4,    10,    10,
       4,     4,    10,    76,     4,   102,    16,    16,    19,    16,
      77,    77,     4,     4,     4,    55,     3,    99,   101,     4,
      75,    90,    90,    90,    90,     4,     4,     4,     4,   105,
       4,     3,   106,   106,     4,     4,   102,     4,     4,    89,
      18,     3,    99,     4,     4,    81,    85,    79,    82,    83,
     105,   106,    16,     3,     4,   102,    18,    99,     4,     4,
       4,     4,     4,     4,    50,     4,     4,   102,    77,     3,
       4,     4,    19,     3,   102,    19,     4,   102,     4
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    73,    74,    74,    75,    75,    76,    77,    77,    78,
      79,    79,    80,    81,    81,    81,    81,    82,    83,    84,
      84,    85,    86,    87,    87,    87,    88,    88,    89,    89,
      90,    90,    91,    92,    92,    93,    93,    94,    94,    95,
      95,    95,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    97,    97,    97,    97,
      98,    99,   100,   100,   100,   100,   101,   101,   101,   101,
     101,   101,   102,   102,   103,   103,   104,   105,   105,   105,
     105,   106,   106,   106,   107,   108,   108,   108,   108,   109,
     109,   110,   110,   111,   111,   112,   112,   113,   113,   113,
     114,   114,   115,   115,   115,   115,   115,   116,   116,   116,
     116,   116,   116,   117,   118,   118,   118,   118,   119,   120,
     120,   121,   122,   122,   123,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   125,   125,   126,   127,
     127,   128,   128,   129,   129,   129,   129,   129,   129,   130,
     130,   130,   130,   131,   131,   132,   133,   133,   134,   135
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     0,     2,     1,
       1,     4,     4,     0,     4,     8,     4,     2,     1,     1,
       2,     4,     1,     1,     1,     1,     1,     1,     0,     2,
       0,     1,     1,     0,     1,     0,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     3,     1,
       2,     2,     2,     2,     2,     2,     2,     3,     3,     2,
       1,     1,     1,     1,     1,     1,     4,     4,     4,     6,
       2,     3,     2,     3,     3,     4,     8,     4,     9,     5,
       3,     2,     0,     2,     0,     2,     1,     1,     5,     5,
       6,     1,     5,     6,     1,     7,     6,     6,     5,     4,
       1,     6,     5,     6,    10,     6,     5,     6,     9,     8,
       7,     6,     5,     5,     5,     5,     5,     6,     6,     6,
       6,     6,     6,     5,     4,     4,     4,     4,     5,     0,
       1,     4,     4,     5,     4,     0,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     5,     5,     1,     0,
       1,     6,     5,     5,     5,     5,     5,     4,     5,     1,
       1,     1,     5,     0,     2,     4,     0,     2,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (&yylloc, lexer, parser, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if WASM_AST_PARSER_DEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined WASM_AST_PARSER_LTYPE_IS_TRIVIAL && WASM_AST_PARSER_LTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, lexer, parser); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, WasmAstLexer* lexer, WasmAstParser* parser)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (lexer);
  YYUSE (parser);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, WasmAstLexer* lexer, WasmAstParser* parser)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, lexer, parser);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, WasmAstLexer* lexer, WasmAstParser* parser)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , lexer, parser);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, lexer, parser); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !WASM_AST_PARSER_DEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !WASM_AST_PARSER_DEBUG */


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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, WasmAstLexer* lexer, WasmAstParser* parser)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (lexer);
  YYUSE (parser);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 5: /* NAT  */
#line 237 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      {}
#line 1616 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 6: /* INT  */
#line 237 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      {}
#line 1622 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 7: /* FLOAT  */
#line 237 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      {}
#line 1628 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 8: /* TEXT  */
#line 237 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      {}
#line 1634 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 9: /* VAR  */
#line 237 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      {}
#line 1640 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 35: /* OFFSET_EQ_NAT  */
#line 237 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      {}
#line 1646 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 36: /* ALIGN_EQ_NAT  */
#line 237 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      {}
#line 1652 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 74: /* non_empty_text_list  */
#line 260 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_text_list(parser->allocator, &((*yyvaluep).text_list)); }
#line 1658 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 75: /* text_list  */
#line 260 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_text_list(parser->allocator, &((*yyvaluep).text_list)); }
#line 1664 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 76: /* quoted_text  */
#line 259 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_string_slice(parser->allocator, &((*yyvaluep).text)); }
#line 1670 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 77: /* value_type_list  */
#line 261 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_type_vector(parser->allocator, &((*yyvaluep).types)); }
#line 1676 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 80: /* func_type  */
#line 251 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_func_signature(parser->allocator, &((*yyvaluep).func_sig)); }
#line 1682 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 81: /* func_sig  */
#line 251 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_func_signature(parser->allocator, &((*yyvaluep).func_sig)); }
#line 1688 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 85: /* type_use  */
#line 263 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_var(parser->allocator, &((*yyvaluep).var)); }
#line 1694 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 87: /* literal  */
#line 257 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_string_slice(parser->allocator, &((*yyvaluep).literal).text); }
#line 1700 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 88: /* var  */
#line 263 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_var(parser->allocator, &((*yyvaluep).var)); }
#line 1706 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 89: /* var_list  */
#line 262 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_var_vector_and_elements(parser->allocator, &((*yyvaluep).vars)); }
#line 1712 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 90: /* bind_var_opt  */
#line 259 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_string_slice(parser->allocator, &((*yyvaluep).text)); }
#line 1718 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 91: /* bind_var  */
#line 259 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_string_slice(parser->allocator, &((*yyvaluep).text)); }
#line 1724 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 92: /* labeling_opt  */
#line 259 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_string_slice(parser->allocator, &((*yyvaluep).text)); }
#line 1730 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 95: /* instr  */
#line 248 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_expr_list(parser->allocator, ((*yyvaluep).expr_list).first); }
#line 1736 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 96: /* plain_instr  */
#line 247 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_expr(parser->allocator, ((*yyvaluep).expr)); }
#line 1742 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 97: /* block_instr  */
#line 247 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_expr(parser->allocator, ((*yyvaluep).expr)); }
#line 1748 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 98: /* block  */
#line 238 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_block(parser->allocator, &((*yyvaluep).block)); }
#line 1754 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 99: /* expr  */
#line 248 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_expr_list(parser->allocator, ((*yyvaluep).expr_list).first); }
#line 1760 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 100: /* expr1  */
#line 248 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_expr_list(parser->allocator, ((*yyvaluep).expr_list).first); }
#line 1766 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 101: /* if_  */
#line 248 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_expr_list(parser->allocator, ((*yyvaluep).expr_list).first); }
#line 1772 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 102: /* instr_list  */
#line 248 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_expr_list(parser->allocator, ((*yyvaluep).expr_list).first); }
#line 1778 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 103: /* expr_list  */
#line 248 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_expr_list(parser->allocator, ((*yyvaluep).expr_list).first); }
#line 1784 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 104: /* const_expr  */
#line 248 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_expr_list(parser->allocator, ((*yyvaluep).expr_list).first); }
#line 1790 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 105: /* func_fields  */
#line 249 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_func_fields(parser->allocator, ((*yyvaluep).func_fields)); }
#line 1796 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 106: /* func_body  */
#line 249 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_func_fields(parser->allocator, ((*yyvaluep).func_fields)); }
#line 1802 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 107: /* func_info  */
#line 250 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_func(parser->allocator, ((*yyvaluep).func)); wasm_free(parser->allocator, ((*yyvaluep).func)); }
#line 1808 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 108: /* func  */
#line 244 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_exported_func(parser->allocator, &((*yyvaluep).exported_func)); }
#line 1814 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 109: /* offset  */
#line 248 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_expr_list(parser->allocator, ((*yyvaluep).expr_list).first); }
#line 1820 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 110: /* elem  */
#line 242 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_elem_segment(parser->allocator, &((*yyvaluep).elem_segment)); }
#line 1826 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 111: /* table  */
#line 246 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_exported_table(parser->allocator, &((*yyvaluep).exported_table)); }
#line 1832 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 112: /* data  */
#line 254 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_data_segment(parser->allocator, &((*yyvaluep).data_segment)); }
#line 1838 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 113: /* memory  */
#line 245 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_exported_memory(parser->allocator, &((*yyvaluep).exported_memory)); }
#line 1844 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 115: /* import_kind  */
#line 253 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_import(parser->allocator, ((*yyvaluep).import)); wasm_free(parser->allocator, ((*yyvaluep).import)); }
#line 1850 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 116: /* import  */
#line 253 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_import(parser->allocator, ((*yyvaluep).import)); wasm_free(parser->allocator, ((*yyvaluep).import)); }
#line 1856 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 117: /* inline_import  */
#line 253 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_import(parser->allocator, ((*yyvaluep).import)); wasm_free(parser->allocator, ((*yyvaluep).import)); }
#line 1862 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 118: /* export_kind  */
#line 243 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_export(parser->allocator, &((*yyvaluep).export_)); }
#line 1868 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 119: /* export  */
#line 243 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_export(parser->allocator, &((*yyvaluep).export_)); }
#line 1874 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 122: /* type_def  */
#line 252 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_func_type(parser->allocator, &((*yyvaluep).func_type)); }
#line 1880 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 123: /* start  */
#line 263 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_var(parser->allocator, &((*yyvaluep).var)); }
#line 1886 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 124: /* module_fields  */
#line 255 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_module(parser->allocator, ((*yyvaluep).module)); wasm_free(parser->allocator, ((*yyvaluep).module)); }
#line 1892 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 125: /* raw_module  */
#line 256 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_raw_module(parser->allocator, &((*yyvaluep).raw_module)); }
#line 1898 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 126: /* module  */
#line 255 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_module(parser->allocator, ((*yyvaluep).module)); wasm_free(parser->allocator, ((*yyvaluep).module)); }
#line 1904 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 127: /* script_var_opt  */
#line 259 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_string_slice(parser->allocator, &((*yyvaluep).text)); }
#line 1910 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 129: /* assertion  */
#line 239 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_command(parser->allocator, ((*yyvaluep).command)); wasm_free(parser->allocator, ((*yyvaluep).command)); }
#line 1916 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 130: /* cmd  */
#line 239 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_command(parser->allocator, ((*yyvaluep).command)); wasm_free(parser->allocator, ((*yyvaluep).command)); }
#line 1922 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 131: /* cmd_list  */
#line 240 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_command_vector_and_elements(parser->allocator, &((*yyvaluep).commands)); }
#line 1928 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 133: /* const_list  */
#line 241 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_const_vector(parser->allocator, &((*yyvaluep).consts)); }
#line 1934 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;

    case 134: /* script  */
#line 258 "src/wasm-ast-parser.y" /* yacc.c:1257  */
      { wasm_destroy_script(&((*yyvaluep).script)); }
#line 1940 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1257  */
        break;


      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (WasmAstLexer* lexer, WasmAstParser* parser)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined WASM_AST_PARSER_LTYPE_IS_TRIVIAL && WASM_AST_PARSER_LTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, lexer, parser);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 276 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WasmTextListNode* node = new_text_list_node(parser->allocator);
      DUPTEXT(node->text, (yyvsp[0].text));
      node->next = NULL;
      (yyval.text_list).first = (yyval.text_list).last = node;
    }
#line 2239 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 3:
#line 282 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.text_list) = (yyvsp[-1].text_list);
      WasmTextListNode* node = new_text_list_node(parser->allocator);
      DUPTEXT(node->text, (yyvsp[0].text));
      node->next = NULL;
      (yyval.text_list).last->next = node;
      (yyval.text_list).last = node;
    }
#line 2252 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 4:
#line 292 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { (yyval.text_list).first = (yyval.text_list).last = NULL; }
#line 2258 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 6:
#line 297 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WasmTextListNode node;
      node.text = (yyvsp[0].text);
      node.next = NULL;
      WasmTextList text_list;
      text_list.first = &node;
      text_list.last = &node;
      void* data;
      size_t size;
      dup_text_list(parser->allocator, &text_list, &data, &size);
      (yyval.text).start = data;
      (yyval.text).length = size;
    }
#line 2276 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 7:
#line 315 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { WASM_ZERO_MEMORY((yyval.types)); }
#line 2282 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 8:
#line 316 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.types) = (yyvsp[-1].types);
      wasm_append_type_value(parser->allocator, &(yyval.types), &(yyvsp[0].type));
    }
#line 2291 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 9:
#line 322 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {}
#line 2297 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 10:
#line 325 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.global));
      (yyval.global).type = (yyvsp[0].type);
      (yyval.global).mutable_ = WASM_FALSE;
    }
#line 2307 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 11:
#line 330 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.global));
      (yyval.global).type = (yyvsp[-1].type);
      (yyval.global).mutable_ = WASM_TRUE;
    }
#line 2317 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 12:
#line 337 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { (yyval.func_sig) = (yyvsp[-1].func_sig); }
#line 2323 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 13:
#line 340 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { WASM_ZERO_MEMORY((yyval.func_sig)); }
#line 2329 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 14:
#line 341 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.func_sig));
      (yyval.func_sig).param_types = (yyvsp[-1].types);
    }
#line 2338 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 15:
#line 345 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.func_sig));
      (yyval.func_sig).param_types = (yyvsp[-5].types);
      (yyval.func_sig).result_types = (yyvsp[-1].types);
    }
#line 2348 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 16:
#line 350 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.func_sig));
      (yyval.func_sig).result_types = (yyvsp[-1].types);
    }
#line 2357 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 17:
#line 357 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { (yyval.table).elem_limits = (yyvsp[-1].limits); }
#line 2363 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 18:
#line 360 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { (yyval.memory).page_limits = (yyvsp[0].limits); }
#line 2369 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 19:
#line 363 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.limits).has_max = WASM_FALSE;
      (yyval.limits).initial = (yyvsp[0].u64);
      (yyval.limits).max = 0;
    }
#line 2379 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 20:
#line 368 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.limits).has_max = WASM_TRUE;
      (yyval.limits).initial = (yyvsp[-1].u64);
      (yyval.limits).max = (yyvsp[0].u64);
    }
#line 2389 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 21:
#line 375 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { (yyval.var) = (yyvsp[-1].var); }
#line 2395 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 22:
#line 381 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      if (WASM_FAILED(wasm_parse_uint64((yyvsp[0].literal).text.start,
                                        (yyvsp[0].literal).text.start + (yyvsp[0].literal).text.length, &(yyval.u64)))) {
        wasm_ast_parser_error(&(yylsp[0]), lexer, parser,
                              "invalid int " PRIstringslice "\"",
                              WASM_PRINTF_STRING_SLICE_ARG((yyvsp[0].literal).text));
      }
    }
#line 2408 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 23:
#line 392 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.literal).type = (yyvsp[0].literal).type;
      DUPTEXT((yyval.literal).text, (yyvsp[0].literal).text);
    }
#line 2417 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 24:
#line 396 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.literal).type = (yyvsp[0].literal).type;
      DUPTEXT((yyval.literal).text, (yyvsp[0].literal).text);
    }
#line 2426 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 25:
#line 400 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.literal).type = (yyvsp[0].literal).type;
      DUPTEXT((yyval.literal).text, (yyvsp[0].literal).text);
    }
#line 2435 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 26:
#line 407 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.var).loc = (yylsp[0]);
      (yyval.var).type = WASM_VAR_TYPE_INDEX;
      (yyval.var).index = (yyvsp[0].u64);
    }
#line 2445 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 27:
#line 412 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.var).loc = (yylsp[0]);
      (yyval.var).type = WASM_VAR_TYPE_NAME;
      DUPTEXT((yyval.var).name, (yyvsp[0].text));
    }
#line 2455 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 28:
#line 419 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { WASM_ZERO_MEMORY((yyval.vars)); }
#line 2461 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 29:
#line 420 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.vars) = (yyvsp[-1].vars);
      wasm_append_var_value(parser->allocator, &(yyval.vars), &(yyvsp[0].var));
    }
#line 2470 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 30:
#line 426 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { WASM_ZERO_MEMORY((yyval.text)); }
#line 2476 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 32:
#line 430 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { DUPTEXT((yyval.text), (yyvsp[0].text)); }
#line 2482 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 33:
#line 434 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { WASM_ZERO_MEMORY((yyval.text)); }
#line 2488 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 35:
#line 439 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { (yyval.u64) = 0; }
#line 2494 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 36:
#line 440 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
    if (WASM_FAILED(wasm_parse_int64((yyvsp[0].text).start, (yyvsp[0].text).start + (yyvsp[0].text).length, &(yyval.u64),
                                     WASM_PARSE_SIGNED_AND_UNSIGNED))) {
      wasm_ast_parser_error(&(yylsp[0]), lexer, parser,
                            "invalid offset \"" PRIstringslice "\"",
                            WASM_PRINTF_STRING_SLICE_ARG((yyvsp[0].text)));
      }
    }
#line 2507 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 37:
#line 450 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { (yyval.u32) = USE_NATURAL_ALIGNMENT; }
#line 2513 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 38:
#line 451 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      if (WASM_FAILED(wasm_parse_int32((yyvsp[0].text).start, (yyvsp[0].text).start + (yyvsp[0].text).length, &(yyval.u32),
                                       WASM_PARSE_UNSIGNED_ONLY))) {
        wasm_ast_parser_error(&(yylsp[0]), lexer, parser,
                              "invalid alignment \"" PRIstringslice "\"",
                              WASM_PRINTF_STRING_SLICE_ARG((yyvsp[0].text)));
      }
    }
#line 2526 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 39:
#line 462 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { (yyval.expr_list) = join_exprs1(&(yylsp[0]), (yyvsp[0].expr)); }
#line 2532 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 40:
#line 463 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { (yyval.expr_list) = join_exprs1(&(yylsp[0]), (yyvsp[0].expr)); }
#line 2538 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 41:
#line 464 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { (yyval.expr_list) = (yyvsp[0].expr_list); }
#line 2544 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 42:
#line 467 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_unreachable_expr(parser->allocator);
    }
#line 2552 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 43:
#line 470 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_nop_expr(parser->allocator);
    }
#line 2560 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 44:
#line 473 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_drop_expr(parser->allocator);
    }
#line 2568 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 45:
#line 476 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_select_expr(parser->allocator);
    }
#line 2576 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 46:
#line 479 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_br_expr(parser->allocator);
      (yyval.expr)->br.var = (yyvsp[0].var);
    }
#line 2585 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 47:
#line 483 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_br_if_expr(parser->allocator);
      (yyval.expr)->br_if.var = (yyvsp[0].var);
    }
#line 2594 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 48:
#line 487 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_br_table_expr(parser->allocator);
      (yyval.expr)->br_table.targets = (yyvsp[-1].vars);
      (yyval.expr)->br_table.default_target = (yyvsp[0].var);
    }
#line 2604 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 49:
#line 492 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_return_expr(parser->allocator);
    }
#line 2612 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 50:
#line 495 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_call_expr(parser->allocator);
      (yyval.expr)->call.var = (yyvsp[0].var);
    }
#line 2621 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 51:
#line 499 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_call_indirect_expr(parser->allocator);
      (yyval.expr)->call_indirect.var = (yyvsp[0].var);
    }
#line 2630 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 52:
#line 503 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_get_local_expr(parser->allocator);
      (yyval.expr)->get_local.var = (yyvsp[0].var);
    }
#line 2639 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 53:
#line 507 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_set_local_expr(parser->allocator);
      (yyval.expr)->set_local.var = (yyvsp[0].var);
    }
#line 2648 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 54:
#line 511 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_tee_local_expr(parser->allocator);
      (yyval.expr)->tee_local.var = (yyvsp[0].var);
    }
#line 2657 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 55:
#line 515 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_get_global_expr(parser->allocator);
      (yyval.expr)->get_global.var = (yyvsp[0].var);
    }
#line 2666 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 56:
#line 519 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_set_global_expr(parser->allocator);
      (yyval.expr)->set_global.var = (yyvsp[0].var);
    }
#line 2675 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 57:
#line 523 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_load_expr(parser->allocator);
      (yyval.expr)->load.opcode = (yyvsp[-2].opcode);
      (yyval.expr)->load.offset = (yyvsp[-1].u64);
      (yyval.expr)->load.align = (yyvsp[0].u32);
    }
#line 2686 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 58:
#line 529 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_store_expr(parser->allocator);
      (yyval.expr)->store.opcode = (yyvsp[-2].opcode);
      (yyval.expr)->store.offset = (yyvsp[-1].u64);
      (yyval.expr)->store.align = (yyvsp[0].u32);
    }
#line 2697 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 59:
#line 535 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_const_expr(parser->allocator);
      (yyval.expr)->const_.loc = (yylsp[-1]);
      if (WASM_FAILED(parse_const((yyvsp[-1].type), (yyvsp[0].literal).type, (yyvsp[0].literal).text.start,
                                  (yyvsp[0].literal).text.start + (yyvsp[0].literal).text.length,
                                  &(yyval.expr)->const_))) {
        wasm_ast_parser_error(&(yylsp[0]), lexer, parser,
                              "invalid literal \"" PRIstringslice "\"",
                              WASM_PRINTF_STRING_SLICE_ARG((yyvsp[0].literal).text));
      }
      wasm_free(parser->allocator, (char*)(yyvsp[0].literal).text.start);
    }
#line 2714 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 60:
#line 547 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_unary_expr(parser->allocator);
      (yyval.expr)->unary.opcode = (yyvsp[0].opcode);
    }
#line 2723 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 61:
#line 551 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_binary_expr(parser->allocator);
      (yyval.expr)->binary.opcode = (yyvsp[0].opcode);
    }
#line 2732 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 62:
#line 555 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_compare_expr(parser->allocator);
      (yyval.expr)->compare.opcode = (yyvsp[0].opcode);
    }
#line 2741 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 63:
#line 559 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_convert_expr(parser->allocator);
      (yyval.expr)->convert.opcode = (yyvsp[0].opcode);
    }
#line 2750 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 64:
#line 563 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_current_memory_expr(parser->allocator);
    }
#line 2758 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 65:
#line 566 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_grow_memory_expr(parser->allocator);
    }
#line 2766 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 66:
#line 571 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_block_expr(parser->allocator);
      (yyval.expr)->block = (yyvsp[-1].block);
      (yyval.expr)->block.label = (yyvsp[-2].text);
    }
#line 2776 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 67:
#line 576 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_loop_expr(parser->allocator);
      (yyval.expr)->loop = (yyvsp[-1].block);
      (yyval.expr)->loop.label = (yyvsp[-2].text);
    }
#line 2786 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 68:
#line 581 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_if_expr(parser->allocator);
      (yyval.expr)->if_.true_ = (yyvsp[-1].block);
      (yyval.expr)->if_.true_.label = (yyvsp[-2].text);
    }
#line 2796 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 69:
#line 586 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr) = wasm_new_if_expr(parser->allocator);
      (yyval.expr)->if_.true_ = (yyvsp[-3].block);
      (yyval.expr)->if_.true_.label = (yyvsp[-4].text);
      (yyval.expr)->if_.false_ = (yyvsp[-1].expr_list).first;
    }
#line 2807 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 70:
#line 594 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.block));
      (yyval.block).sig = (yyvsp[-1].types);
      (yyval.block).first = (yyvsp[0].expr_list).first;
    }
#line 2817 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 71:
#line 602 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { (yyval.expr_list) = (yyvsp[-1].expr_list); }
#line 2823 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 72:
#line 606 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr_list) = join_exprs2(&(yylsp[-1]), &(yyvsp[0].expr_list), (yyvsp[-1].expr));
    }
#line 2831 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 73:
#line 609 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WasmExpr* expr = wasm_new_block_expr(parser->allocator);
      expr->block = (yyvsp[0].block);
      expr->block.label = (yyvsp[-1].text);
      (yyval.expr_list) = join_exprs1(&(yylsp[-2]), expr);
    }
#line 2842 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 74:
#line 615 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WasmExpr* expr = wasm_new_loop_expr(parser->allocator);
      expr->loop = (yyvsp[0].block);
      expr->loop.label = (yyvsp[-1].text);
      (yyval.expr_list) = join_exprs1(&(yylsp[-2]), expr);
    }
#line 2853 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 75:
#line 621 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr_list) = (yyvsp[0].expr_list);
      WasmExpr* if_ = (yyvsp[0].expr_list).last;
      assert(if_->type == WASM_EXPR_TYPE_IF);
      if_->if_.true_.label = (yyvsp[-2].text);
      if_->if_.true_.sig = (yyvsp[-1].types);
    }
#line 2865 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 76:
#line 630 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WasmExpr* expr = wasm_new_if_expr(parser->allocator);
      expr->if_.true_.first = (yyvsp[-5].expr_list).first;
      expr->if_.false_ = (yyvsp[-1].expr_list).first;
      (yyval.expr_list) = join_exprs1(&(yylsp[-7]), expr);
    }
#line 2876 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 77:
#line 636 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WasmExpr* expr = wasm_new_if_expr(parser->allocator);
      expr->if_.true_.first = (yyvsp[-1].expr_list).first;
      (yyval.expr_list) = join_exprs1(&(yylsp[-3]), expr);
    }
#line 2886 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 78:
#line 641 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WasmExpr* expr = wasm_new_if_expr(parser->allocator);
      expr->if_.true_.first = (yyvsp[-5].expr_list).first;
      expr->if_.false_ = (yyvsp[-1].expr_list).first;
      (yyval.expr_list) = join_exprs2(&(yylsp[-8]), &(yyvsp[-8].expr_list), expr);
    }
#line 2897 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 79:
#line 647 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WasmExpr* expr = wasm_new_if_expr(parser->allocator);
      expr->if_.true_.first = (yyvsp[-1].expr_list).first;
      (yyval.expr_list) = join_exprs2(&(yylsp[-4]), &(yyvsp[-4].expr_list), expr);
    }
#line 2907 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 80:
#line 652 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WasmExpr* expr = wasm_new_if_expr(parser->allocator);
      expr->if_.true_.first = (yyvsp[-1].expr_list).first;
      expr->if_.false_ = (yyvsp[0].expr_list).first;
      (yyval.expr_list) = join_exprs2(&(yylsp[-2]), &(yyvsp[-2].expr_list), expr);
    }
#line 2918 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 81:
#line 658 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WasmExpr* expr = wasm_new_if_expr(parser->allocator);
      expr->if_.true_.first = (yyvsp[0].expr_list).first;
      (yyval.expr_list) = join_exprs2(&(yylsp[-1]), &(yyvsp[-1].expr_list), expr);
    }
#line 2928 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 82:
#line 666 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { WASM_ZERO_MEMORY((yyval.expr_list)); }
#line 2934 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 83:
#line 667 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr_list).first = (yyvsp[-1].expr_list).first;
      (yyvsp[-1].expr_list).last->next = (yyvsp[0].expr_list).first;
      (yyval.expr_list).last = (yyvsp[0].expr_list).last ? (yyvsp[0].expr_list).last : (yyvsp[-1].expr_list).last;
      (yyval.expr_list).size = (yyvsp[-1].expr_list).size + (yyvsp[0].expr_list).size;
    }
#line 2945 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 84:
#line 675 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { WASM_ZERO_MEMORY((yyval.expr_list)); }
#line 2951 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 85:
#line 676 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr_list).first = (yyvsp[-1].expr_list).first;
      (yyvsp[-1].expr_list).last->next = (yyvsp[0].expr_list).first;
      (yyval.expr_list).last = (yyvsp[0].expr_list).last ? (yyvsp[0].expr_list).last : (yyvsp[-1].expr_list).last;
      (yyval.expr_list).size = (yyvsp[-1].expr_list).size + (yyvsp[0].expr_list).size;
    }
#line 2962 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 88:
#line 690 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.func_fields) = new_func_field(parser->allocator);
      (yyval.func_fields)->type = WASM_FUNC_FIELD_TYPE_RESULT_TYPES;
      (yyval.func_fields)->types = (yyvsp[-2].types);
      (yyval.func_fields)->next = (yyvsp[0].func_fields);
    }
#line 2973 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 89:
#line 696 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.func_fields) = new_func_field(parser->allocator);
      (yyval.func_fields)->type = WASM_FUNC_FIELD_TYPE_PARAM_TYPES;
      (yyval.func_fields)->types = (yyvsp[-2].types);
      (yyval.func_fields)->next = (yyvsp[0].func_fields);
    }
#line 2984 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 90:
#line 702 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.func_fields) = new_func_field(parser->allocator);
      (yyval.func_fields)->type = WASM_FUNC_FIELD_TYPE_BOUND_PARAM;
      (yyval.func_fields)->bound_type.loc = (yylsp[-4]);
      (yyval.func_fields)->bound_type.name = (yyvsp[-3].text);
      (yyval.func_fields)->bound_type.type = (yyvsp[-2].type);
      (yyval.func_fields)->next = (yyvsp[0].func_fields);
    }
#line 2997 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 91:
#line 712 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.func_fields) = new_func_field(parser->allocator);
      (yyval.func_fields)->type = WASM_FUNC_FIELD_TYPE_EXPRS;
      (yyval.func_fields)->first_expr = (yyvsp[0].expr_list).first;
      (yyval.func_fields)->next = NULL;
    }
#line 3008 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 92:
#line 718 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.func_fields) = new_func_field(parser->allocator);
      (yyval.func_fields)->type = WASM_FUNC_FIELD_TYPE_LOCAL_TYPES;
      (yyval.func_fields)->types = (yyvsp[-2].types);
      (yyval.func_fields)->next = (yyvsp[0].func_fields);
    }
#line 3019 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 93:
#line 724 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.func_fields) = new_func_field(parser->allocator);
      (yyval.func_fields)->type = WASM_FUNC_FIELD_TYPE_BOUND_LOCAL;
      (yyval.func_fields)->bound_type.loc = (yylsp[-4]);
      (yyval.func_fields)->bound_type.name = (yyvsp[-3].text);
      (yyval.func_fields)->bound_type.type = (yyvsp[-2].type);
      (yyval.func_fields)->next = (yyvsp[0].func_fields);
    }
#line 3032 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 94:
#line 734 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.func) = new_func(parser->allocator);
      WasmFuncField* field = (yyvsp[0].func_fields);

      while (field) {
        WasmFuncField* next = field->next;
        switch (field->type) {
          case WASM_FUNC_FIELD_TYPE_EXPRS:
            (yyval.func)->first_expr = field->first_expr;
            break;

          case WASM_FUNC_FIELD_TYPE_PARAM_TYPES:
          case WASM_FUNC_FIELD_TYPE_LOCAL_TYPES: {
            WasmTypeVector* types =
                field->type == WASM_FUNC_FIELD_TYPE_PARAM_TYPES
                    ? &(yyval.func)->decl.sig.param_types
                    : &(yyval.func)->local_types;
            wasm_extend_types(parser->allocator, types, &field->types);
            wasm_destroy_type_vector(parser->allocator, &field->types);
            break;
          }

          case WASM_FUNC_FIELD_TYPE_BOUND_PARAM:
          case WASM_FUNC_FIELD_TYPE_BOUND_LOCAL: {
            WasmTypeVector* types;
            WasmBindingHash* bindings;
            if (field->type == WASM_FUNC_FIELD_TYPE_BOUND_PARAM) {
              types = &(yyval.func)->decl.sig.param_types;
              bindings = &(yyval.func)->param_bindings;
            } else {
              types = &(yyval.func)->local_types;
              bindings = &(yyval.func)->local_bindings;
            }

            wasm_append_type_value(parser->allocator, types,
                                   &field->bound_type.type);
            WasmBinding* binding = wasm_insert_binding(
                parser->allocator, bindings, &field->bound_type.name);
            binding->loc = field->bound_type.loc;
            binding->index = types->size - 1;
            break;
          }

          case WASM_FUNC_FIELD_TYPE_RESULT_TYPES:
            (yyval.func)->decl.sig.result_types = field->types;
            break;
        }

        /* we steal memory from the func field, but not the linked list nodes */
        wasm_free(parser->allocator, field);
        field = next;
      }
    }
#line 3090 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 95:
#line 789 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.exported_func));
      (yyval.exported_func).func = (yyvsp[-1].func);
      (yyval.exported_func).func->decl.flags |= WASM_FUNC_DECLARATION_FLAG_HAS_FUNC_TYPE;
      (yyval.exported_func).func->decl.type_var = (yyvsp[-2].var);
      (yyval.exported_func).func->name = (yyvsp[-4].text);
      (yyval.exported_func).export_ = (yyvsp[-3].optional_export);
    }
#line 3103 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 96:
#line 798 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.exported_func));
      (yyval.exported_func).func = (yyvsp[-1].func);
      (yyval.exported_func).func->decl.flags |= WASM_FUNC_DECLARATION_FLAG_HAS_FUNC_TYPE;
      (yyval.exported_func).func->decl.type_var = (yyvsp[-2].var);
      (yyval.exported_func).func->name = (yyvsp[-3].text);
    }
#line 3115 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 97:
#line 805 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.exported_func));
      (yyval.exported_func).func = (yyvsp[-1].func);
      (yyval.exported_func).func->name = (yyvsp[-3].text);
      (yyval.exported_func).export_ = (yyvsp[-2].optional_export);
    }
#line 3126 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 98:
#line 812 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.exported_func));
      (yyval.exported_func).func = (yyvsp[-1].func);
      (yyval.exported_func).func->name = (yyvsp[-2].text);
    }
#line 3136 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 99:
#line 822 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.expr_list) = (yyvsp[-1].expr_list);
    }
#line 3144 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 101:
#line 829 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.elem_segment).table_var = (yyvsp[-3].var);
      (yyval.elem_segment).offset = (yyvsp[-2].expr_list).first;
      (yyval.elem_segment).vars = (yyvsp[-1].vars);
    }
#line 3154 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 102:
#line 834 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.elem_segment).table_var.type = WASM_VAR_TYPE_INDEX;
      (yyval.elem_segment).table_var.index = 0;
      (yyval.elem_segment).offset = (yyvsp[-2].expr_list).first;
      (yyval.elem_segment).vars = (yyvsp[-1].vars);
    }
#line 3165 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 103:
#line 843 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.exported_table).table = (yyvsp[-1].table);
      (yyval.exported_table).table.name = (yyvsp[-3].text);
      (yyval.exported_table).has_elem_segment = WASM_FALSE;
      (yyval.exported_table).export_ = (yyvsp[-2].optional_export);
    }
#line 3176 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 104:
#line 850 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WasmExpr* expr = wasm_new_const_expr(parser->allocator);
      expr->loc = (yylsp[-8]);
      expr->const_.type = WASM_TYPE_I32;
      expr->const_.u32 = 0;

      WASM_ZERO_MEMORY((yyval.exported_table));
      (yyval.exported_table).table.name = (yyvsp[-7].text);
      (yyval.exported_table).table.elem_limits.initial = (yyvsp[-2].vars).size;
      (yyval.exported_table).table.elem_limits.max = (yyvsp[-2].vars).size;
      (yyval.exported_table).table.elem_limits.has_max = WASM_TRUE;
      (yyval.exported_table).has_elem_segment = WASM_TRUE;
      (yyval.exported_table).elem_segment.offset = expr;
      (yyval.exported_table).elem_segment.vars = (yyvsp[-2].vars);
      (yyval.exported_table).export_ = (yyvsp[-6].optional_export);
    }
#line 3197 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 105:
#line 869 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.data_segment).memory_var = (yyvsp[-3].var);
      (yyval.data_segment).offset = (yyvsp[-2].expr_list).first;
      dup_text_list(parser->allocator, &(yyvsp[-1].text_list), &(yyval.data_segment).data, &(yyval.data_segment).size);
      wasm_destroy_text_list(parser->allocator, &(yyvsp[-1].text_list));
    }
#line 3208 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 106:
#line 875 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.data_segment).memory_var.type = WASM_VAR_TYPE_INDEX;
      (yyval.data_segment).memory_var.index = 0;
      (yyval.data_segment).offset = (yyvsp[-2].expr_list).first;
      dup_text_list(parser->allocator, &(yyvsp[-1].text_list), &(yyval.data_segment).data, &(yyval.data_segment).size);
      wasm_destroy_text_list(parser->allocator, &(yyvsp[-1].text_list));
    }
#line 3220 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 107:
#line 885 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.exported_memory));
      (yyval.exported_memory).memory = (yyvsp[-1].memory);
      (yyval.exported_memory).memory.name = (yyvsp[-3].text);
      (yyval.exported_memory).has_data_segment = WASM_FALSE;
      (yyval.exported_memory).export_ = (yyvsp[-2].optional_export);
    }
#line 3232 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 108:
#line 892 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WasmExpr* expr = wasm_new_const_expr(parser->allocator);
      expr->loc = (yylsp[-7]);
      expr->const_.type = WASM_TYPE_I32;
      expr->const_.u32 = 0;

      WASM_ZERO_MEMORY((yyval.exported_memory));
      (yyval.exported_memory).has_data_segment = WASM_TRUE;
      (yyval.exported_memory).data_segment.offset = expr;
      dup_text_list(parser->allocator, &(yyvsp[-2].text_list), &(yyval.exported_memory).data_segment.data,
                    &(yyval.exported_memory).data_segment.size);
      wasm_destroy_text_list(parser->allocator, &(yyvsp[-2].text_list));
      uint32_t byte_size = WASM_ALIGN_UP_TO_PAGE((yyval.exported_memory).data_segment.size);
      uint32_t page_size = WASM_BYTES_TO_PAGES(byte_size);
      (yyval.exported_memory).memory.name = (yyvsp[-6].text);
      (yyval.exported_memory).memory.page_limits.initial = page_size;
      (yyval.exported_memory).memory.page_limits.max = page_size;
      (yyval.exported_memory).memory.page_limits.has_max = WASM_TRUE;
      (yyval.exported_memory).export_ = (yyvsp[-5].optional_export);
    }
#line 3257 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 109:
#line 913 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WasmExpr* expr = wasm_new_const_expr(parser->allocator);
      expr->loc = (yylsp[-6]);
      expr->const_.type = WASM_TYPE_I32;
      expr->const_.u32 = 0;

      WASM_ZERO_MEMORY((yyval.exported_memory));
      (yyval.exported_memory).has_data_segment = WASM_TRUE;
      (yyval.exported_memory).data_segment.offset = expr;
      dup_text_list(parser->allocator, &(yyvsp[-2].text_list), &(yyval.exported_memory).data_segment.data,
                    &(yyval.exported_memory).data_segment.size);
      wasm_destroy_text_list(parser->allocator, &(yyvsp[-2].text_list));
      uint32_t byte_size = WASM_ALIGN_UP_TO_PAGE((yyval.exported_memory).data_segment.size);
      uint32_t page_size = WASM_BYTES_TO_PAGES(byte_size);
      (yyval.exported_memory).memory.name = (yyvsp[-5].text);
      (yyval.exported_memory).memory.page_limits.initial = page_size;
      (yyval.exported_memory).memory.page_limits.max = page_size;
      (yyval.exported_memory).memory.page_limits.has_max = WASM_TRUE;
      (yyval.exported_memory).export_.has_export = WASM_FALSE;
    }
#line 3282 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 110:
#line 936 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.exported_global));
      (yyval.exported_global).global = (yyvsp[-2].global);
      (yyval.exported_global).global.name = (yyvsp[-4].text);
      (yyval.exported_global).global.init_expr = (yyvsp[-1].expr_list).first;
      (yyval.exported_global).export_ = (yyvsp[-3].optional_export);
    }
#line 3294 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 111:
#line 943 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.exported_global));
      (yyval.exported_global).global = (yyvsp[-2].global);
      (yyval.exported_global).global.name = (yyvsp[-3].text);
      (yyval.exported_global).global.init_expr = (yyvsp[-1].expr_list).first;
      (yyval.exported_global).export_.has_export = WASM_FALSE;
    }
#line 3306 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 112:
#line 956 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.import) = new_import(parser->allocator);
      (yyval.import)->kind = WASM_EXTERNAL_KIND_FUNC;
      (yyval.import)->func.name = (yyvsp[-2].text);
      (yyval.import)->func.decl.flags = WASM_FUNC_DECLARATION_FLAG_HAS_FUNC_TYPE;
      (yyval.import)->func.decl.type_var = (yyvsp[-1].var);
    }
#line 3318 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 113:
#line 963 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.import) = new_import(parser->allocator);
      (yyval.import)->kind = WASM_EXTERNAL_KIND_FUNC;
      (yyval.import)->func.name = (yyvsp[-2].text);
      (yyval.import)->func.decl.sig = (yyvsp[-1].func_sig);
    }
#line 3329 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 114:
#line 969 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.import) = new_import(parser->allocator);
      (yyval.import)->kind = WASM_EXTERNAL_KIND_TABLE;
      (yyval.import)->table = (yyvsp[-1].table);
      (yyval.import)->table.name = (yyvsp[-2].text);
    }
#line 3340 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 115:
#line 975 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.import) = new_import(parser->allocator);
      (yyval.import)->kind = WASM_EXTERNAL_KIND_MEMORY;
      (yyval.import)->memory = (yyvsp[-1].memory);
      (yyval.import)->memory.name = (yyvsp[-2].text);
    }
#line 3351 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 116:
#line 981 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.import) = new_import(parser->allocator);
      (yyval.import)->kind = WASM_EXTERNAL_KIND_GLOBAL;
      (yyval.import)->global = (yyvsp[-1].global);
      (yyval.import)->global.name = (yyvsp[-2].text);
    }
#line 3362 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 117:
#line 989 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.import) = (yyvsp[-1].import);
      (yyval.import)->module_name = (yyvsp[-3].text);
      (yyval.import)->field_name = (yyvsp[-2].text);
    }
#line 3372 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 118:
#line 994 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.import) = (yyvsp[-2].import);
      (yyval.import)->kind = WASM_EXTERNAL_KIND_FUNC;
      (yyval.import)->func.name = (yyvsp[-3].text);
      (yyval.import)->func.decl.flags = WASM_FUNC_DECLARATION_FLAG_HAS_FUNC_TYPE;
      (yyval.import)->func.decl.type_var = (yyvsp[-1].var);
    }
#line 3384 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1001 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.import) = (yyvsp[-2].import);
      (yyval.import)->kind = WASM_EXTERNAL_KIND_FUNC;
      (yyval.import)->func.name = (yyvsp[-3].text);
      (yyval.import)->func.decl.sig = (yyvsp[-1].func_sig);
    }
#line 3395 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1007 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.import) = (yyvsp[-2].import);
      (yyval.import)->kind = WASM_EXTERNAL_KIND_TABLE;
      (yyval.import)->table = (yyvsp[-1].table);
      (yyval.import)->table.name = (yyvsp[-3].text);
    }
#line 3406 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1013 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.import) = (yyvsp[-2].import);
      (yyval.import)->kind = WASM_EXTERNAL_KIND_MEMORY;
      (yyval.import)->memory = (yyvsp[-1].memory);
      (yyval.import)->memory.name = (yyvsp[-3].text);
    }
#line 3417 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1019 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.import) = (yyvsp[-2].import);
      (yyval.import)->kind = WASM_EXTERNAL_KIND_GLOBAL;
      (yyval.import)->global = (yyvsp[-1].global);
      (yyval.import)->global.name = (yyvsp[-3].text);
    }
#line 3428 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1028 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.import) = new_import(parser->allocator);
      (yyval.import)->module_name = (yyvsp[-2].text);
      (yyval.import)->field_name = (yyvsp[-1].text);
    }
#line 3438 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1036 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.export_));
      (yyval.export_).kind = WASM_EXTERNAL_KIND_FUNC;
      (yyval.export_).var = (yyvsp[-1].var);
    }
#line 3448 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1041 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.export_));
      (yyval.export_).kind = WASM_EXTERNAL_KIND_TABLE;
      (yyval.export_).var = (yyvsp[-1].var);
    }
#line 3458 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1046 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.export_));
      (yyval.export_).kind = WASM_EXTERNAL_KIND_MEMORY;
      (yyval.export_).var = (yyvsp[-1].var);
    }
#line 3468 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1051 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.export_));
      (yyval.export_).kind = WASM_EXTERNAL_KIND_GLOBAL;
      (yyval.export_).var = (yyvsp[-1].var);
    }
#line 3478 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1058 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.export_) = (yyvsp[-1].export_);
      (yyval.export_).name = (yyvsp[-2].text);
    }
#line 3487 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1065 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { 
      WASM_ZERO_MEMORY((yyval.optional_export));
      (yyval.optional_export).has_export = WASM_FALSE;
    }
#line 3496 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1072 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.optional_export));
      (yyval.optional_export).has_export = WASM_TRUE;
      (yyval.optional_export).export_.name = (yyvsp[-1].text);
    }
#line 3506 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1083 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.func_type));
      (yyval.func_type).sig = (yyvsp[-1].func_sig);
    }
#line 3515 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1087 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.func_type).name = (yyvsp[-2].text);
      (yyval.func_type).sig = (yyvsp[-1].func_sig);
    }
#line 3524 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1094 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { (yyval.var) = (yyvsp[-1].var); }
#line 3530 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1098 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.module) = new_module(parser->allocator);
    }
#line 3538 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1101 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.module) = (yyvsp[-1].module);
      WasmModuleField* field;
      APPEND_FIELD_TO_LIST((yyval.module), field, FUNC_TYPE, func_type, (yylsp[0]), (yyvsp[0].func_type));
      APPEND_ITEM_TO_VECTOR((yyval.module), FuncType, func_type, func_types,
                            &field->func_type);
      INSERT_BINDING((yyval.module), func_type, func_types, (yylsp[0]), (yyvsp[0].func_type).name);
    }
#line 3551 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1109 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.module) = (yyvsp[-1].module);
      WasmModuleField* field;
      APPEND_FIELD_TO_LIST((yyval.module), field, GLOBAL, global, (yylsp[0]), (yyvsp[0].exported_global).global);
      APPEND_ITEM_TO_VECTOR((yyval.module), Global, global, globals, &field->global);
      INSERT_BINDING((yyval.module), global, globals, (yylsp[0]), (yyvsp[0].exported_global).global.name);
      APPEND_INLINE_EXPORT((yyval.module), GLOBAL, (yylsp[0]), (yyvsp[0].exported_global), (yyval.module)->globals.size - 1);
    }
#line 3564 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1117 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.module) = (yyvsp[-1].module);
      WasmModuleField* field;
      APPEND_FIELD_TO_LIST((yyval.module), field, TABLE, table, (yylsp[0]), (yyvsp[0].exported_table).table);
      APPEND_ITEM_TO_VECTOR((yyval.module), Table, table, tables, &field->table);
      INSERT_BINDING((yyval.module), table, tables, (yylsp[0]), (yyvsp[0].exported_table).table.name);
      APPEND_INLINE_EXPORT((yyval.module), TABLE, (yylsp[0]), (yyvsp[0].exported_table), (yyval.module)->tables.size - 1);

      if ((yyvsp[0].exported_table).has_elem_segment) {
        WasmModuleField* elem_segment_field;
        APPEND_FIELD_TO_LIST((yyval.module), elem_segment_field, ELEM_SEGMENT, elem_segment,
                             (yylsp[0]), (yyvsp[0].exported_table).elem_segment);
        APPEND_ITEM_TO_VECTOR((yyval.module), ElemSegment, elem_segment, elem_segments,
                              &elem_segment_field->elem_segment);
      }

    }
#line 3586 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1134 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.module) = (yyvsp[-1].module);
      WasmModuleField* field;
      APPEND_FIELD_TO_LIST((yyval.module), field, MEMORY, memory, (yylsp[0]), (yyvsp[0].exported_memory).memory);
      APPEND_ITEM_TO_VECTOR((yyval.module), Memory, memory, memories, &field->memory);
      INSERT_BINDING((yyval.module), memory, memories, (yylsp[0]), (yyvsp[0].exported_memory).memory.name);
      APPEND_INLINE_EXPORT((yyval.module), MEMORY, (yylsp[0]), (yyvsp[0].exported_memory), (yyval.module)->memories.size - 1);

      if ((yyvsp[0].exported_memory).has_data_segment) {
        WasmModuleField* data_segment_field;
        APPEND_FIELD_TO_LIST((yyval.module), data_segment_field, DATA_SEGMENT, data_segment,
                             (yylsp[0]), (yyvsp[0].exported_memory).data_segment);
        APPEND_ITEM_TO_VECTOR((yyval.module), DataSegment, data_segment, data_segments,
                              &data_segment_field->data_segment);
      }
    }
#line 3607 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1150 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.module) = (yyvsp[-1].module);
      WasmModuleField* field;
      APPEND_FIELD_TO_LIST((yyval.module), field, FUNC, func, (yylsp[0]), *(yyvsp[0].exported_func).func);
      append_implicit_func_declaration(parser->allocator, &(yylsp[0]), (yyval.module),
                                       &field->func.decl);
      APPEND_ITEM_TO_VECTOR((yyval.module), Func, func, funcs, &field->func);
      INSERT_BINDING((yyval.module), func, funcs, (yylsp[0]), (yyvsp[0].exported_func).func->name);
      APPEND_INLINE_EXPORT((yyval.module), FUNC, (yylsp[0]), (yyvsp[0].exported_func), (yyval.module)->funcs.size - 1);
      wasm_free(parser->allocator, (yyvsp[0].exported_func).func);
    }
#line 3623 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1161 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.module) = (yyvsp[-1].module);
      WasmModuleField* field;
      APPEND_FIELD_TO_LIST((yyval.module), field, ELEM_SEGMENT, elem_segment, (yylsp[0]), (yyvsp[0].elem_segment));
      APPEND_ITEM_TO_VECTOR((yyval.module), ElemSegment, elem_segment, elem_segments,
                            &field->elem_segment);
    }
#line 3635 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1168 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.module) = (yyvsp[-1].module);
      WasmModuleField* field;
      APPEND_FIELD_TO_LIST((yyval.module), field, DATA_SEGMENT, data_segment, (yylsp[0]), (yyvsp[0].data_segment));
      APPEND_ITEM_TO_VECTOR((yyval.module), DataSegment, data_segment, data_segments,
                            &field->data_segment);
    }
#line 3647 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1175 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.module) = (yyvsp[-1].module);
      WasmModuleField* field;
      APPEND_FIELD_TO_LIST((yyval.module), field, START, start, (yylsp[0]), (yyvsp[0].var));
      (yyval.module)->start = &field->start;
    }
#line 3658 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1181 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.module) = (yyvsp[-1].module);
      WasmModuleField* field;
      APPEND_FIELD_TO_LIST((yyval.module), field, IMPORT, import, (yylsp[0]), *(yyvsp[0].import));
      switch ((yyvsp[0].import)->kind) {
        case WASM_EXTERNAL_KIND_FUNC:
          append_implicit_func_declaration(parser->allocator, &(yylsp[0]), (yyval.module),
                                           &field->import.func.decl);
          APPEND_ITEM_TO_VECTOR((yyval.module), Func, func, funcs, &field->import.func);
          INSERT_BINDING((yyval.module), func, funcs, (yylsp[0]), field->import.func.name);
          (yyval.module)->num_func_imports++;
          CHECK_IMPORT_ORDERING((yyval.module), func, funcs, (yylsp[0]));
          break;
        case WASM_EXTERNAL_KIND_TABLE:
          APPEND_ITEM_TO_VECTOR((yyval.module), Table, table, tables, &field->import.table);
          INSERT_BINDING((yyval.module), table, tables, (yylsp[0]), field->import.table.name);
          (yyval.module)->num_table_imports++;
          CHECK_IMPORT_ORDERING((yyval.module), table, tables, (yylsp[0]));
          break;
        case WASM_EXTERNAL_KIND_MEMORY:
          APPEND_ITEM_TO_VECTOR((yyval.module), Memory, memory, memories,
                                &field->import.memory);
          INSERT_BINDING((yyval.module), memory, memories, (yylsp[0]), field->import.memory.name);
          (yyval.module)->num_memory_imports++;
          CHECK_IMPORT_ORDERING((yyval.module), memory, memories, (yylsp[0]));
          break;
        case WASM_EXTERNAL_KIND_GLOBAL:
          APPEND_ITEM_TO_VECTOR((yyval.module), Global, global, globals,
                                &field->import.global);
          INSERT_BINDING((yyval.module), global, globals, (yylsp[0]), field->import.global.name);
          (yyval.module)->num_global_imports++;
          CHECK_IMPORT_ORDERING((yyval.module), global, globals, (yylsp[0]));
          break;
        case WASM_NUM_EXTERNAL_KINDS:
          assert(0);
          break;
      }
      wasm_free(parser->allocator, (yyvsp[0].import));
      APPEND_ITEM_TO_VECTOR((yyval.module), Import, import, imports, &field->import);
    }
#line 3703 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1221 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.module) = (yyvsp[-1].module);
      WasmModuleField* field = wasm_append_module_field(parser->allocator, (yyval.module));
      APPEND_FIELD_TO_LIST((yyval.module), field, EXPORT, export_, (yylsp[0]), (yyvsp[0].export_));
      APPEND_ITEM_TO_VECTOR((yyval.module), Export, export, exports, &field->export_);
      INSERT_BINDING((yyval.module), export, exports, (yylsp[0]), (yyvsp[0].export_).name);
    }
#line 3715 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1231 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.raw_module).type = WASM_RAW_MODULE_TYPE_TEXT;
      (yyval.raw_module).text = (yyvsp[-1].module);
      (yyval.raw_module).text->name = (yyvsp[-2].text);
      (yyval.raw_module).loc = (yylsp[-3]);

      /* resolve func type variables where the signature was not specified
       * explicitly */
      size_t i;
      for (i = 0; i < (yyvsp[-1].module)->funcs.size; ++i) {
        WasmFunc* func = (yyvsp[-1].module)->funcs.data[i];
        if (wasm_decl_has_func_type(&func->decl) &&
            is_empty_signature(&func->decl.sig)) {
          WasmFuncType* func_type =
              wasm_get_func_type_by_var((yyvsp[-1].module), &func->decl.type_var);
          if (func_type) {
            func->decl.sig = func_type->sig;
            func->decl.flags |= WASM_FUNC_DECLARATION_FLAG_SHARED_SIGNATURE;
          }
        }
      }
    }
#line 3742 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1253 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.raw_module).type = WASM_RAW_MODULE_TYPE_BINARY;
      (yyval.raw_module).binary.name = (yyvsp[-2].text);
      (yyval.raw_module).loc = (yylsp[-3]);
      dup_text_list(parser->allocator, &(yyvsp[-1].text_list), &(yyval.raw_module).binary.data, &(yyval.raw_module).binary.size);
      wasm_destroy_text_list(parser->allocator, &(yyvsp[-1].text_list));
    }
#line 3754 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1263 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      if ((yyvsp[0].raw_module).type == WASM_RAW_MODULE_TYPE_TEXT) {
        (yyval.module) = (yyvsp[0].raw_module).text;
      } else {
        assert((yyvsp[0].raw_module).type == WASM_RAW_MODULE_TYPE_BINARY);
        (yyval.module) = new_module(parser->allocator);
        WasmReadBinaryOptions options = WASM_READ_BINARY_OPTIONS_DEFAULT;
        BinaryErrorCallbackData user_data;
        user_data.loc = &(yyvsp[0].raw_module).loc;
        user_data.lexer = lexer;
        user_data.parser = parser;
        WasmBinaryErrorHandler error_handler;
        error_handler.on_error = on_read_binary_error;
        error_handler.user_data = &user_data;
        wasm_read_binary_ast(parser->allocator, (yyvsp[0].raw_module).binary.data, (yyvsp[0].raw_module).binary.size,
                             &options, &error_handler, (yyval.module));
        wasm_free(parser->allocator, (yyvsp[0].raw_module).binary.data);
        (yyval.module)->name = (yyvsp[0].raw_module).binary.name;
      }
    }
#line 3779 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1288 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { WASM_ZERO_MEMORY((yyval.text)); }
#line 3785 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1289 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { DUPTEXT((yyval.text), (yyvsp[0].text)); }
#line 3791 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1293 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.action));
      (yyval.action).loc = (yylsp[-4]);
      (yyval.action).module_var_name = (yyvsp[-3].text);
      (yyval.action).type = WASM_ACTION_TYPE_INVOKE;
      (yyval.action).invoke.name = (yyvsp[-2].text);
      (yyval.action).invoke.args = (yyvsp[-1].consts);
    }
#line 3804 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1301 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      WASM_ZERO_MEMORY((yyval.action));
      (yyval.action).loc = (yylsp[-3]);
      (yyval.action).module_var_name = (yyvsp[-2].text);
      (yyval.action).type = WASM_ACTION_TYPE_GET;
      (yyval.action).invoke.name = (yyvsp[-1].text);
    }
#line 3816 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1311 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.command) = new_command(parser->allocator);
      (yyval.command)->type = WASM_COMMAND_TYPE_ASSERT_MALFORMED;
      (yyval.command)->assert_malformed.module = (yyvsp[-2].raw_module);
      (yyval.command)->assert_malformed.text = (yyvsp[-1].text);
    }
#line 3827 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1317 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.command) = new_command(parser->allocator);
      (yyval.command)->type = WASM_COMMAND_TYPE_ASSERT_INVALID;
      (yyval.command)->assert_invalid.module = (yyvsp[-2].raw_module);
      (yyval.command)->assert_invalid.text = (yyvsp[-1].text);
    }
#line 3838 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1323 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.command) = new_command(parser->allocator);
      (yyval.command)->type = WASM_COMMAND_TYPE_ASSERT_UNLINKABLE;
      (yyval.command)->assert_unlinkable.module = (yyvsp[-2].raw_module);
      (yyval.command)->assert_unlinkable.text = (yyvsp[-1].text);
    }
#line 3849 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1329 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.command) = new_command(parser->allocator);
      (yyval.command)->type = WASM_COMMAND_TYPE_ASSERT_RETURN;
      (yyval.command)->assert_return.action = (yyvsp[-2].action);
      (yyval.command)->assert_return.expected = (yyvsp[-1].consts);
    }
#line 3860 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1335 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.command) = new_command(parser->allocator);
      (yyval.command)->type = WASM_COMMAND_TYPE_ASSERT_RETURN_NAN;
      (yyval.command)->assert_return_nan.action = (yyvsp[-1].action);
    }
#line 3870 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1340 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.command) = new_command(parser->allocator);
      (yyval.command)->type = WASM_COMMAND_TYPE_ASSERT_TRAP;
      (yyval.command)->assert_trap.action = (yyvsp[-2].action);
      (yyval.command)->assert_trap.text = (yyvsp[-1].text);
    }
#line 3881 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1349 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.command) = new_command(parser->allocator);
      (yyval.command)->type = WASM_COMMAND_TYPE_ACTION;
      (yyval.command)->action = (yyvsp[0].action);
    }
#line 3891 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1355 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.command) = new_command(parser->allocator);
      (yyval.command)->type = WASM_COMMAND_TYPE_MODULE;
      (yyval.command)->module = *(yyvsp[0].module);
      wasm_free(parser->allocator, (yyvsp[0].module));
    }
#line 3902 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1361 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.command) = new_command(parser->allocator);
      (yyval.command)->type = WASM_COMMAND_TYPE_REGISTER;
      (yyval.command)->register_.module_name = (yyvsp[-2].text);
      (yyval.command)->register_.module_var_name = (yyvsp[-1].text);
    }
#line 3913 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1369 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { WASM_ZERO_MEMORY((yyval.commands)); }
#line 3919 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1370 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.commands) = (yyvsp[-1].commands);
      wasm_append_command_value(parser->allocator, &(yyval.commands), (yyvsp[0].command));
      wasm_free(parser->allocator, (yyvsp[0].command));
    }
#line 3929 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1378 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.const_).loc = (yylsp[-2]);
      if (WASM_FAILED(parse_const((yyvsp[-2].type), (yyvsp[-1].literal).type, (yyvsp[-1].literal).text.start,
                                  (yyvsp[-1].literal).text.start + (yyvsp[-1].literal).text.length, &(yyval.const_)))) {
        wasm_ast_parser_error(&(yylsp[-1]), lexer, parser,
                              "invalid literal \"" PRIstringslice "\"",
                              WASM_PRINTF_STRING_SLICE_ARG((yyvsp[-1].literal).text));
      }
      wasm_free(parser->allocator, (char*)(yyvsp[-1].literal).text.start);
    }
#line 3944 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1390 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    { WASM_ZERO_MEMORY((yyval.consts)); }
#line 3950 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1391 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.consts) = (yyvsp[-1].consts);
      wasm_append_const_value(parser->allocator, &(yyval.consts), &(yyvsp[0].const_));
    }
#line 3959 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1398 "src/wasm-ast-parser.y" /* yacc.c:1646  */
    {
      (yyval.script).commands = (yyvsp[0].commands);
      parser->script = (yyval.script);
    }
#line 3968 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
    break;


#line 3972 "src/prebuilt/wasm-ast-parser-gen.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, lexer, parser, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, lexer, parser, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc, lexer, parser);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, lexer, parser);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, lexer, parser, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, lexer, parser);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, lexer, parser);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1410 "src/wasm-ast-parser.y" /* yacc.c:1906  */


static void append_expr_list(WasmExprList* expr_list, WasmExprList* expr) {
  if (!expr->first)
    return;
  if (expr_list->last)
    expr_list->last->next = expr->first;
  else
    expr_list->first = expr->first;
  expr_list->last = expr->last;
  expr_list->size += expr->size;
}

static void append_expr(WasmExprList* expr_list, WasmExpr* expr) {
  if (expr_list->last)
    expr_list->last->next = expr;
  else
    expr_list->first = expr;
  expr_list->last = expr;
  expr_list->size++;
}

static WasmExprList join_exprs1(WasmLocation* loc, WasmExpr* expr1) {
  WasmExprList result;
  WASM_ZERO_MEMORY(result);
  append_expr(&result, expr1);
  expr1->loc = *loc;
  return result;
}

static WasmExprList join_exprs2(WasmLocation* loc, WasmExprList* expr1,
                                WasmExpr* expr2) {
  WasmExprList result;
  WASM_ZERO_MEMORY(result);
  append_expr_list(&result, expr1);
  append_expr(&result, expr2);
  expr2->loc = *loc;
  return result;
}

static WasmResult parse_const(WasmType type,
                              WasmLiteralType literal_type,
                              const char* s,
                              const char* end,
                              WasmConst* out) {
  out->type = type;
  switch (type) {
    case WASM_TYPE_I32:
      return wasm_parse_int32(s, end, &out->u32,
                              WASM_PARSE_SIGNED_AND_UNSIGNED);
    case WASM_TYPE_I64:
      return wasm_parse_int64(s, end, &out->u64,
                              WASM_PARSE_SIGNED_AND_UNSIGNED);
    case WASM_TYPE_F32:
      return wasm_parse_float(literal_type, s, end, &out->f32_bits);
    case WASM_TYPE_F64:
      return wasm_parse_double(literal_type, s, end, &out->f64_bits);
    default:
      assert(0);
      break;
  }
  return WASM_ERROR;
}

static size_t copy_string_contents(WasmStringSlice* text, char* dest) {
  const char* src = text->start + 1;
  const char* end = text->start + text->length - 1;

  char* dest_start = dest;

  while (src < end) {
    if (*src == '\\') {
      src++;
      switch (*src) {
        case 'n':
          *dest++ = '\n';
          break;
        case 't':
          *dest++ = '\t';
          break;
        case '\\':
          *dest++ = '\\';
          break;
        case '\'':
          *dest++ = '\'';
          break;
        case '\"':
          *dest++ = '\"';
          break;
        default: {
          /* The string should be validated already, so we know this is a hex
           * sequence */
          uint32_t hi;
          uint32_t lo;
          if (WASM_SUCCEEDED(wasm_parse_hexdigit(src[0], &hi)) &&
              WASM_SUCCEEDED(wasm_parse_hexdigit(src[1], &lo))) {
            *dest++ = (hi << 4) | lo;
          } else {
            assert(0);
          }
          src++;
          break;
        }
      }
      src++;
    } else {
      *dest++ = *src++;
    }
  }
  /* return the data length */
  return dest - dest_start;
}

static void dup_text_list(WasmAllocator* allocator,
                          WasmTextList* text_list,
                          void** out_data,
                          size_t* out_size) {
  /* walk the linked list to see how much total space is needed */
  size_t total_size = 0;
  WasmTextListNode* node;
  for (node = text_list->first; node; node = node->next) {
    /* Always allocate enough space for the entire string including the escape
     * characters. It will only get shorter, and this way we only have to
     * iterate through the string once. */
    const char* src = node->text.start + 1;
    const char* end = node->text.start + node->text.length - 1;
    size_t size = (end > src) ? (end - src) : 0;
    total_size += size;
  }
  char* result = wasm_alloc(allocator, total_size, 1);
  char* dest = result;
  for (node = text_list->first; node; node = node->next) {
    size_t actual_size = copy_string_contents(&node->text, dest);
    dest += actual_size;
  }
  *out_data = result;
  *out_size = dest - result;
}

static WasmBool is_empty_signature(WasmFuncSignature* sig) {
  return sig->result_types.size == 0 && sig->param_types.size == 0;
}

static void append_implicit_func_declaration(WasmAllocator* allocator,
                                             WasmLocation* loc,
                                             WasmModule* module,
                                             WasmFuncDeclaration* decl) {
  if (wasm_decl_has_func_type(decl))
    return;

  int sig_index = wasm_get_func_type_index_by_decl(module, decl);
  if (sig_index == -1) {
    wasm_append_implicit_func_type(allocator, loc, module, &decl->sig);
  } else {
    /* signature already exists, share that one and destroy this one */
    wasm_destroy_func_signature(allocator, &decl->sig);
    WasmFuncSignature* sig = &module->func_types.data[sig_index]->sig;
    decl->sig = *sig;
  }

  decl->flags |= WASM_FUNC_DECLARATION_FLAG_SHARED_SIGNATURE;
}

WasmResult wasm_parse_ast(WasmAstLexer* lexer,
                          struct WasmScript* out_script,
                          WasmSourceErrorHandler* error_handler) {
  WasmAstParser parser;
  WASM_ZERO_MEMORY(parser);
  WasmAllocator* allocator = wasm_ast_lexer_get_allocator(lexer);
  parser.allocator = allocator;
  parser.error_handler = error_handler;
  out_script->allocator = allocator;
  int result = wasm_ast_parser_parse(lexer, &parser);
  out_script->commands = parser.script.commands;
  return result == 0 && parser.errors == 0 ? WASM_OK : WASM_ERROR;
}

static void on_read_binary_error(uint32_t offset, const char* error,
                                 void* user_data) {
  BinaryErrorCallbackData* data = user_data;
  if (offset == WASM_UNKNOWN_OFFSET) {
    wasm_ast_parser_error(data->loc, data->lexer, data->parser,
                          "error in binary module: %s", error);
  } else {
    wasm_ast_parser_error(data->loc, data->lexer, data->parser,
                          "error in binary module: @0x%08x: %s", offset, error);
  }
}

/* see comment above definition of YYMAXDEPTH at the top of this file */
WASM_STATIC_ASSERT(YYSTACK_ALLOC_MAXIMUM >= UINT32_MAX);
WASM_STATIC_ASSERT(YYSTACK_BYTES((uint64_t)YYMAXDEPTH) <= UINT32_MAX);