# C++ Language Reference

A comprehensive reference guide to C++ language features organized by knowledge dependency.

Source: [cppreference.com C++ Language Reference](https://en.cppreference.com/w/cpp/language.html)

## 📚 Browse by C++ Version

Looking for features by C++ standard version? Check out the [**by_version**](./by_version/) folder:
- [C++98/03](./by_version/cpp98_03.md) - Original standard
- [C++11](./by_version/cpp11.md) - Major modernization (move semantics, lambdas, auto)
- [C++14](./by_version/cpp14.md) - Refinements (generic lambdas, variable templates)
- [C++17](./by_version/cpp17.md) - Structured bindings, if constexpr, CTAD
- [C++20](./by_version/cpp20.md) - Concepts, modules, coroutines, ranges
- [C++23](./by_version/cpp23.md) - Current standard (std::expected, std::print, deducing this)
- [C++26](./by_version/cpp26.md) - ⚠️ Upcoming (reflection, pattern matching, contracts)

## Table of Contents

### [01 - Foundational Concepts](./01_foundational_concepts/)

#### [Basic concepts](./01_foundational_concepts/basic_concepts.md)
- [Basic concepts](https://en.cppreference.com/w/cpp/language/basics.html)
- [The as-if rule](https://en.cppreference.com/w/cpp/language/as_if.html)
- [Translation phases](https://en.cppreference.com/w/cpp/language/translation_phases.html)
- [main function](https://en.cppreference.com/w/cpp/language/main_function.html)
- [Comments](https://en.cppreference.com/w/cpp/comments.html)
- [Character sets and encodings](https://en.cppreference.com/w/cpp/language/charset.html)
- [Escape sequences](https://en.cppreference.com/w/cpp/language/escape.html)
- [ASCII chart](https://en.cppreference.com/w/cpp/language/ascii.html)
- [Punctuation](https://en.cppreference.com/w/cpp/language/punctuators.html)
- [Names and identifiers](https://en.cppreference.com/w/cpp/language/name.html)

### [02 - Types and Objects](./02_types_and_objects/)

#### [Types](./02_types_and_objects/types.md)
- [Types](https://en.cppreference.com/w/cpp/language/type-id.html)
- [Fundamental types](https://en.cppreference.com/w/cpp/language/types.html)
- [Incomplete type](https://en.cppreference.com/w/cpp/language/incomplete_type.html)

#### [Object](./02_types_and_objects/object.md)
- [Object](https://en.cppreference.com/w/cpp/language/objects.html)
- [Scope](https://en.cppreference.com/w/cpp/language/scope.html)
- [Lifetime](https://en.cppreference.com/w/cpp/language/lifetime.html)
- [Memory model](https://en.cppreference.com/w/cpp/language/memory_model.html)

#### [Definitions and ODR](./02_types_and_objects/definitions_and_odr.md)
- [Definitions and ODR](https://en.cppreference.com/w/cpp/language/definition.html)

#### [Name lookup](./02_types_and_objects/name_lookup.md)
- [Name lookup](https://en.cppreference.com/w/cpp/language/lookup.html)
- [Qualified name lookup](https://en.cppreference.com/w/cpp/language/qualified_lookup.html)
- [Unqualified name lookup](https://en.cppreference.com/w/cpp/language/unqualified_lookup.html)
- [Argument-dependent lookup (ADL)](https://en.cppreference.com/w/cpp/language/adl.html)

### [03 - Keywords and Preprocessor](./03_keywords_and_preprocessor/)

#### [Keywords](./03_keywords_and_preprocessor/keywords.md)
- [Keywords](https://en.cppreference.com/w/cpp/keywords.html)

#### [Preprocessor](./03_keywords_and_preprocessor/preprocessor.md)
- [Preprocessor](https://en.cppreference.com/w/cpp/preprocessor.html)
- [#if - #ifdef - #ifndef - #elif](https://en.cppreference.com/w/cpp/preprocessor/conditional.html)
- [#elifdef - #elifndef](https://en.cppreference.com/w/cpp/preprocessor/conditional.html) (C++23)
- [#define - # - ##](https://en.cppreference.com/w/cpp/preprocessor/replace.html)
- [#include](https://en.cppreference.com/w/cpp/preprocessor/include.html)
- [#pragma](https://en.cppreference.com/w/cpp/preprocessor/impl.html)
- [#line](https://en.cppreference.com/w/cpp/preprocessor/line.html)
- [#error](https://en.cppreference.com/w/cpp/preprocessor/warning.html)
- [#warning](https://en.cppreference.com/w/cpp/preprocessor/warning.html) (C++23)

### [03a - Modules](./03a_modules/)

#### [Modules](./03a_modules/modules.md) (C++20)
- [Modules](https://en.cppreference.com/w/cpp/language/modules.html) (C++20)
- [Module declaration](https://en.cppreference.com/w/cpp/language/modules.html#Module_declarations)
- [Primary module interface unit](https://en.cppreference.com/w/cpp/language/modules.html#Module_declarations)
- [Module implementation units](https://en.cppreference.com/w/cpp/language/modules.html#Module_declarations)
- [Export declarations](https://en.cppreference.com/w/cpp/language/modules.html#Exporting_declarations_and_definitions)
- [Import declarations](https://en.cppreference.com/w/cpp/language/modules.html#Importing_modules_and_header_units)
- [Importing header units](https://en.cppreference.com/w/cpp/language/modules.html#Importing_modules_and_header_units)
- [Global module fragment](https://en.cppreference.com/w/cpp/language/modules.html#Global_module_fragment)
- [Private module fragment](https://en.cppreference.com/w/cpp/language/modules.html#Private_module_fragment)
- [Module partitions](https://en.cppreference.com/w/cpp/language/modules.html#Module_partitions)
- [Module ownership](https://en.cppreference.com/w/cpp/language/modules.html#Module_ownership)

### [04 - Expressions](./04_expressions/)

#### [Expressions](./04_expressions/expressions.md)
- [Expressions](https://en.cppreference.com/w/cpp/language/expressions.html)
- [Value categories](https://en.cppreference.com/w/cpp/language/value_category.html)
- [Evaluation order](https://en.cppreference.com/w/cpp/language/eval_order.html)
- [Constant expressions](https://en.cppreference.com/w/cpp/language/constant_expression.html)

#### [Operators](./04_expressions/operators.md)
- [Operators](https://en.cppreference.com/w/cpp/language/expressions.html#Operators)
- [Assignment operators](https://en.cppreference.com/w/cpp/language/operator_assignment.html)
- [Arithmetic operators](https://en.cppreference.com/w/cpp/language/operator_arithmetic.html)
- [Increment and decrement](https://en.cppreference.com/w/cpp/language/operator_incdec.html)
- [Logical operators](https://en.cppreference.com/w/cpp/language/operator_logical.html)
- [Comparison operators](https://en.cppreference.com/w/cpp/language/operator_comparison.html)
- [Member access operators](https://en.cppreference.com/w/cpp/language/operator_member_access.html)
- [Other operators](https://en.cppreference.com/w/cpp/language/operator_other.html)
- [sizeof](https://en.cppreference.com/w/cpp/language/sizeof.html)
- [alignof](https://en.cppreference.com/w/cpp/language/alignof.html) (C++11)
- [typeid](https://en.cppreference.com/w/cpp/language/typeid.html)
- [new](https://en.cppreference.com/w/cpp/language/new.html)
- [delete](https://en.cppreference.com/w/cpp/language/delete.html)
- [throw](https://en.cppreference.com/w/cpp/language/throw.html)
- [noexcept operator](https://en.cppreference.com/w/cpp/language/noexcept.html) (C++11)

#### [Conversions](./04_expressions/conversions.md)
- [Copy elision](https://en.cppreference.com/w/cpp/language/copy_elision.html) (C++17 guaranteed)
- [Implicit conversions](https://en.cppreference.com/w/cpp/language/implicit_conversion.html)
- [const_cast](https://en.cppreference.com/w/cpp/language/const_cast.html)
- [static_cast](https://en.cppreference.com/w/cpp/language/static_cast.html)
- [dynamic_cast](https://en.cppreference.com/w/cpp/language/dynamic_cast.html)
- [reinterpret_cast](https://en.cppreference.com/w/cpp/language/reinterpret_cast.html)
- [C-style cast](https://en.cppreference.com/w/cpp/language/explicit_cast.html)
- [User-defined conversion](https://en.cppreference.com/w/cpp/language/cast_operator.html)

#### [Literals](./04_expressions/literals.md)
- [Literals](https://en.cppreference.com/w/cpp/language/expressions.html#Literals)
- [Integer literals](https://en.cppreference.com/w/cpp/language/integer_literal.html)
- [Floating-point literals](https://en.cppreference.com/w/cpp/language/floating_literal.html)
- [Character literals](https://en.cppreference.com/w/cpp/language/character_literal.html)
- [String literals](https://en.cppreference.com/w/cpp/language/string_literal.html)
- [Boolean literals](https://en.cppreference.com/w/cpp/language/bool_literal.html)
- [nullptr](https://en.cppreference.com/w/cpp/language/nullptr.html) (C++11)
- [User-defined literals](https://en.cppreference.com/w/cpp/language/user_literal.html) (C++11)

### [05 - Declarations](./05_declarations/)

#### [Declarations](./05_declarations/declarations.md)
- [Declarations](https://en.cppreference.com/w/cpp/language/declarations.html)
- [Conflicting declarations](https://en.cppreference.com/w/cpp/language/conflicting_declarations.html)

#### [Storage and linkage](./05_declarations/storage_and_linkage.md)
- [Storage duration and linkage](https://en.cppreference.com/w/cpp/language/storage_duration.html)
- [Translation-unit-local](https://en.cppreference.com/w/cpp/language/tu_local.html) (C++20)
- [Language linkage](https://en.cppreference.com/w/cpp/language/language_linkage.html)

#### [Namespaces](./05_declarations/namespaces.md)
- [Namespace declaration](https://en.cppreference.com/w/cpp/language/namespace.html)
- [Namespace alias](https://en.cppreference.com/w/cpp/language/namespace_alias.html)

#### [Compound types](./05_declarations/compound_types.md)
- [References](https://en.cppreference.com/w/cpp/language/reference.html)
- [Pointers](https://en.cppreference.com/w/cpp/language/pointer.html)
- [Arrays](https://en.cppreference.com/w/cpp/language/array.html)

#### [Structured bindings and enumerations](./05_declarations/structured_bindings_and_enumerations.md)
- [Structured bindings](https://en.cppreference.com/w/cpp/language/structured_binding.html) (C++17)
- [Enumerations and enumerators](https://en.cppreference.com/w/cpp/language/enum.html)

#### [Specifiers and qualifiers](./05_declarations/specifiers_and_qualifiers.md)
- [inline specifier](https://en.cppreference.com/w/cpp/language/inline.html)
- [Inline assembly](https://en.cppreference.com/w/cpp/language/asm.html)
- [volatile qualifier](https://en.cppreference.com/w/cpp/language/cv.html)
- [const qualifier](https://en.cppreference.com/w/cpp/language/cv.html)
- [constexpr specifier](https://en.cppreference.com/w/cpp/language/constexpr.html) (C++11)
- [consteval specifier](https://en.cppreference.com/w/cpp/language/consteval.html) (C++20)
- [constinit specifier](https://en.cppreference.com/w/cpp/language/constinit.html) (C++20)
- [alignas specifier](https://en.cppreference.com/w/cpp/language/alignas.html) (C++11)

#### [Type specifiers](./05_declarations/type_specifiers.md)
- [auto](https://en.cppreference.com/w/cpp/language/auto.html) (C++11)
- [decltype](https://en.cppreference.com/w/cpp/language/decltype.html) (C++11)
- [Elaborated type specifier](https://en.cppreference.com/w/cpp/language/elaborated_type_specifier.html)

#### [Attributes](./05_declarations/attributes.md)
- [Attributes](https://en.cppreference.com/w/cpp/language/attributes.html) (C++11)

#### [Compile-time assertions](./05_declarations/compile_time_assertions.md)
- [static_assert](https://en.cppreference.com/w/cpp/language/static_assert.html) (C++11)

#### [Type aliases](./05_declarations/type_aliases.md)
- [typedef declaration](https://en.cppreference.com/w/cpp/language/typedef.html)
- [Type alias, alias template](https://en.cppreference.com/w/cpp/language/type_alias.html) (C++11)

### [06 - Initialization](./06_initialization/)

#### [Initialization](./06_initialization/initialization.md)
- [Initialization](https://en.cppreference.com/w/cpp/language/initialization.html)

#### [Basic initialization forms](./06_initialization/basic_initialization_forms.md)
- [Default-initialization](https://en.cppreference.com/w/cpp/language/default_initialization.html)
- [Value-initialization](https://en.cppreference.com/w/cpp/language/value_initialization.html)
- [Copy-initialization](https://en.cppreference.com/w/cpp/language/copy_initialization.html)
- [Direct-initialization](https://en.cppreference.com/w/cpp/language/direct_initialization.html)
- [Aggregate initialization](https://en.cppreference.com/w/cpp/language/aggregate_initialization.html)
- [List-initialization](https://en.cppreference.com/w/cpp/language/list_initialization.html) (C++11)
- [Reference initialization](https://en.cppreference.com/w/cpp/language/reference_initialization.html)

#### [Non-local variable initialization](./06_initialization/non_local_variable_initialization.md)
- [Zero initialization](https://en.cppreference.com/w/cpp/language/zero_initialization.html)
- [Constant initialization](https://en.cppreference.com/w/cpp/language/constant_initialization.html)
- [Ordered dynamic initialization](https://en.cppreference.com/w/cpp/language/initialization.html#Non-local_variables)
- [Unordered dynamic initialization](https://en.cppreference.com/w/cpp/language/initialization.html#Non-local_variables)
- [Deferred dynamic initialization](https://en.cppreference.com/w/cpp/language/initialization.html#Non-local_variables)

### [07 - Functions](./07_functions/)

#### [Functions](./07_functions/functions.md)
- [Functions](https://en.cppreference.com/w/cpp/language/functions.html)
- [Function declaration](https://en.cppreference.com/w/cpp/language/function.html)
- [Default arguments](https://en.cppreference.com/w/cpp/language/default_arguments.html)
- [Variadic arguments](https://en.cppreference.com/w/cpp/language/variadic_arguments.html)
- [Lambda expression](https://en.cppreference.com/w/cpp/language/lambda.html) (C++11)

#### [Function resolution and overloading](./07_functions/function_resolution_and_overloading.md)
- [Overload resolution](https://en.cppreference.com/w/cpp/language/overload_resolution.html)
- [Operator overloading](https://en.cppreference.com/w/cpp/language/operators.html)
- [Address of an overload set](https://en.cppreference.com/w/cpp/language/overloaded_address.html)

#### [Advanced function types](./07_functions/advanced_function_types.md)
- [Coroutines](https://en.cppreference.com/w/cpp/language/coroutines.html) (C++20)
- [Replacement functions](https://en.cppreference.com/w/cpp/language/replacement_function.html)

### [08 - Statements](./08_statements/)

#### [Statements](./08_statements/statements.md)
- [Statements](https://en.cppreference.com/w/cpp/language/statements.html)

#### [Conditional statements](./08_statements/conditional_statements.md)
- [if](https://en.cppreference.com/w/cpp/language/if.html)
- [if constexpr](https://en.cppreference.com/w/cpp/language/if.html#Constexpr_if) (C++17)
- [if consteval](https://en.cppreference.com/w/cpp/language/if.html#Consteval_if) (C++23)
- [switch](https://en.cppreference.com/w/cpp/language/switch.html)

#### [Iteration statements](./08_statements/iteration_statements.md)
- [for](https://en.cppreference.com/w/cpp/language/for.html)
- [range-for](https://en.cppreference.com/w/cpp/language/range-for.html) (C++11)
- [while](https://en.cppreference.com/w/cpp/language/while.html)
- [do-while](https://en.cppreference.com/w/cpp/language/do.html)

#### [Jump statements](./08_statements/jump_statements.md)
- [continue](https://en.cppreference.com/w/cpp/language/continue.html)
- [break](https://en.cppreference.com/w/cpp/language/break.html)
- [goto](https://en.cppreference.com/w/cpp/language/goto.html)
- [return](https://en.cppreference.com/w/cpp/language/return.html)

#### [Special statements](./08_statements/special_statements.md)
- [contract_assert](https://en.cppreference.com/w/cpp/language/contract_assert.html) (C++26)
- [synchronized/atomic](https://en.cppreference.com/w/cpp/language/transactional_memory.html) (TM TS)

### [09 - Classes](./09_classes/)

#### [Classes](./09_classes/classes.md)
- [Classes](https://en.cppreference.com/w/cpp/language/classes.html)

#### [Basic class concepts](./09_classes/basic_class_concepts.md)
- [Class types](https://en.cppreference.com/w/cpp/language/class.html)
- [Union types](https://en.cppreference.com/w/cpp/language/union.html)
- [injected-class-name](https://en.cppreference.com/w/cpp/language/injected-class-name.html)

#### [Class members](./09_classes/class_members.md)
- [Data members](https://en.cppreference.com/w/cpp/language/data_members.html)
- [Bit-fields](https://en.cppreference.com/w/cpp/language/bit_field.html)
- [Member functions](https://en.cppreference.com/w/cpp/language/member_functions.html)
- [The this pointer](https://en.cppreference.com/w/cpp/language/this.html)
- [Static members](https://en.cppreference.com/w/cpp/language/static.html)
- [Nested classes](https://en.cppreference.com/w/cpp/language/nested_classes.html)

#### [Inheritance and derived classes](./09_classes/inheritance_and_derived_classes.md)
- [Derived class](https://en.cppreference.com/w/cpp/language/derived_class.html)
- [using-declaration](https://en.cppreference.com/w/cpp/language/using_declaration.html)
- [Empty base optimization (EBO)](https://en.cppreference.com/w/cpp/language/ebo.html)
- [Virtual function](https://en.cppreference.com/w/cpp/language/virtual.html)
- [Abstract class](https://en.cppreference.com/w/cpp/language/abstract_class.html)
- [override specifier](https://en.cppreference.com/w/cpp/language/override.html) (C++11)
- [final specifier](https://en.cppreference.com/w/cpp/language/final.html) (C++11)

#### [Special member functions](./09_classes/special_member_functions.md)
- [Default constructor](https://en.cppreference.com/w/cpp/language/default_constructor.html)
- [Copy constructor](https://en.cppreference.com/w/cpp/language/copy_constructor.html)
- [Move constructor](https://en.cppreference.com/w/cpp/language/move_constructor.html) (C++11)
- [Copy assignment operator](https://en.cppreference.com/w/cpp/language/copy_assignment.html)
- [Move assignment operator](https://en.cppreference.com/w/cpp/language/move_assignment.html) (C++11)
- [Destructor](https://en.cppreference.com/w/cpp/language/destructor.html)

#### [Special member function control](./09_classes/special_member_function_control.md)
- [Explicitly-defaulted functions](https://en.cppreference.com/w/cpp/language/function.html#Explicitly-defaulted_functions) (C++11)
- [Deleted functions](https://en.cppreference.com/w/cpp/language/function.html#Deleted_functions) (C++11)
- [Default comparisons](https://en.cppreference.com/w/cpp/language/default_comparisons.html) (C++20)

#### [Access control](./09_classes/access_control.md)
- [Access specifiers](https://en.cppreference.com/w/cpp/language/access.html)
- [friend declaration](https://en.cppreference.com/w/cpp/language/friend.html)

#### [Conversion functions](./09_classes/conversion_functions.md)
- [Converting constructor](https://en.cppreference.com/w/cpp/language/converting_constructor.html)
- [Conversion function](https://en.cppreference.com/w/cpp/language/cast_operator.html)
- [explicit specifier](https://en.cppreference.com/w/cpp/language/explicit.html)

### [10 - Templates](./10_templates/)

#### [Templates](./10_templates/templates.md)
- [Templates](https://en.cppreference.com/w/cpp/language/templates.html)

#### [Template fundamentals](./10_templates/template_fundamentals.md)
- [Template parameters](https://en.cppreference.com/w/cpp/language/template_parameters.html)
- [Template arguments](https://en.cppreference.com/w/cpp/language/template_arguments.html)

#### [Template types](./10_templates/template_types.md)
- [Class template](https://en.cppreference.com/w/cpp/language/class_template.html)
- [Function template](https://en.cppreference.com/w/cpp/language/function_template.html)
- [Variable template](https://en.cppreference.com/w/cpp/language/variable_template.html) (C++14)
- [Class member template](https://en.cppreference.com/w/cpp/language/member_template.html)

#### [Template argument deduction](./10_templates/template_argument_deduction.md)
- [Function template argument deduction](https://en.cppreference.com/w/cpp/language/template_argument_deduction.html)
- [Class template argument deduction (CTAD)](https://en.cppreference.com/w/cpp/language/ctad.html) (C++17)

#### [Template specialization](./10_templates/template_specialization.md)
- [Explicit specialization](https://en.cppreference.com/w/cpp/language/template_specialization.html)
- [Partial specialization](https://en.cppreference.com/w/cpp/language/partial_specialization.html)

#### [Advanced template features](./10_templates/advanced_template_features.md)
- [Parameter packs](https://en.cppreference.com/w/cpp/language/parameter_pack.html) (C++11)
- [sizeof...](https://en.cppreference.com/w/cpp/language/sizeof....html) (C++11)
- [Fold expressions](https://en.cppreference.com/w/cpp/language/fold.html) (C++17)

#### [Constraints and concepts](./10_templates/constraints_and_concepts.md)
- [Constraints and concepts](https://en.cppreference.com/w/cpp/language/constraints.html) (C++20)
- [requires expression](https://en.cppreference.com/w/cpp/language/requires.html) (C++20)

#### [Dependent names](./10_templates/dependent_names.md)
- [Dependent names](https://en.cppreference.com/w/cpp/language/dependent_name.html)
- [SFINAE](https://en.cppreference.com/w/cpp/language/sfinae.html)

### [11 - Exceptions](./11_exceptions/)

#### [Exceptions](./11_exceptions/exceptions.md)
- [Exceptions](https://en.cppreference.com/w/cpp/language/exceptions.html)

#### [Exception handling](./11_exceptions/exception_handling.md)
- [try block](https://en.cppreference.com/w/cpp/language/try.html)
- [Throwing exceptions](https://en.cppreference.com/w/cpp/language/throw.html)
- [Handling exceptions](https://en.cppreference.com/w/cpp/language/catch.html)

#### [Exception specification](./11_exceptions/exception_specification.md)
- [noexcept specification](https://en.cppreference.com/w/cpp/language/noexcept_spec.html) (C++11)
- [Dynamic exception specification](https://en.cppreference.com/w/cpp/language/except_spec.html) (until C++17)

#### [Exception operator](./11_exceptions/exception_operator.md)
- [noexcept operator](https://en.cppreference.com/w/cpp/language/noexcept.html) (C++11)

### [12 - Miscellaneous](./12_miscellaneous/)

#### [Miscellaneous](./12_miscellaneous/miscellaneous.md)
- [History of C++](https://en.cppreference.com/w/cpp/language/history.html)
- [Extending the namespace std](https://en.cppreference.com/w/cpp/language/extending_std.html)
- [AFO - Algorithm function objects](https://en.cppreference.com/w/cpp/algorithm/ranges.html#Algorithm_function_objects)
- [CPO - Customization Point Objects](https://en.cppreference.com/w/cpp/ranges/cpo.html)
- [IFNDR - Ill-formed, No Diagnostic Required](https://en.cppreference.com/w/cpp/ndr.html)
- [NDR - No Diagnostic Required](https://en.cppreference.com/w/cpp/ndr.html)
- [NTBS - Null-Terminated Byte String](https://en.cppreference.com/w/cpp/string/byte.html)
- [NTTP - Non-Type Template Parameter](https://en.cppreference.com/w/cpp/language/template_parameters.html#Constant_template_parameter)
- [RAO - Range Adaptor Objects](https://en.cppreference.com/w/cpp/ranges.html#Range_adaptor_objects)
- [SOCCC - select_on_container_copy_construction](https://en.cppreference.com/w/cpp/memory/allocator_traits/select_on_container_copy_construction.html)
- [TMP - Template Metaprogramming](https://en.cppreference.com/w/cpp/language/templates.html)

#### [Idioms](./12_miscellaneous/idioms.md)
- [Curiously Recurring Template Pattern (CRTP)](https://en.cppreference.com/w/cpp/language/crtp.html)
- [Pointer to implementation (PIMPL)](https://en.cppreference.com/w/cpp/language/pimpl.html)
- [Resource acquisition is initialization (RAII)](https://en.cppreference.com/w/cpp/language/raii.html)
- [Rule of three/five/zero](https://en.cppreference.com/w/cpp/language/rule_of_three.html)
- [Zero-overhead principle](https://en.cppreference.com/w/cpp/language/Zero-overhead_principle.html)

## C++ Version Coverage

This reference covers C++ standards from C++98 through C++26 (draft), with version markers indicated where applicable:
- C++11
- C++14
- C++17
- C++20
- C++23
- C++26

## Navigation

Topics are organized by knowledge dependency, starting with foundational concepts and progressing to advanced features. Each topic links directly to the authoritative cppreference.com documentation.
