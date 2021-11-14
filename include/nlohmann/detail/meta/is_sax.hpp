#pragma once

#include <cstdint> // size_t
#include <utility> // declval
#include <string> // string

#include <nlohmann/detail/meta/detected.hpp>
#include <nlohmann/detail/meta/type_traits.hpp>

namespace nlohmann
{
namespace detail
{
template <
    typename Derived,
    typename SAX,
    typename LexerType,
    typename...Ts >
struct sax_call_function
{
    static constexpr bool no_lexer = std::is_same<LexerType, void>::value;

    static constexpr bool detected_call_base =
        is_detected_exact<bool, Derived::template call_base_t, SAX>::value;

    static constexpr bool detected_call_with_pos =
        is_detected_exact<bool, Derived::template call_base_t, SAX, std::size_t>::value;

    static constexpr bool detected_call_with_lex =
        !no_lexer &&
        is_detected_exact<bool, Derived::template call_base_t, SAX, const LexerType>::value;

    static constexpr bool valid =
        detected_call_base ||
        detected_call_with_pos ||
        detected_call_with_lex;
    
    
    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    std::is_same<SaxT, SAX>::value &&
    std::is_same<LexT, LexerType>::value &&
    sax_call_function<Derived, SaxT, LexT, Ts...>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, Ts...ts, std::size_t pos)
    {
        return Derived::do_call(sax, std::forward<Ts>(ts)..., pos); //1
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    std::is_same<SaxT, SAX>::value &&
    std::is_same<LexT, LexerType>::value &&
    !sax_call_function<Derived, SaxT, LexT, Ts...>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, Ts...ts, std::size_t pos)
    {
        return Derived::do_call(sax, std::forward<Ts>(ts)...); //2
    }
    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    std::is_same<SaxT, SAX>::value &&
    std::is_same<LexT, LexerType>::value &&
    !sax_call_function<Derived, SaxT, LexT, Ts...>::no_lexer &&
    sax_call_function<Derived, SaxT, LexT, Ts...>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, Ts...ts, const LexT& lex)
    {
        return Derived::do_call(sax, std::forward<Ts>(ts)..., lex); //3
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    std::is_same<SaxT, SAX>::value &&
    std::is_same<LexT, LexerType>::value &&
    !sax_call_function<Derived, SaxT, LexT, Ts...>::no_lexer &&
    !sax_call_function<Derived, SaxT, LexT, Ts...>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, Ts...ts, const LexT& lex)
    {
        return call(sax, std::forward<Ts>(ts)..., lex.get_position().chars_read_total);//4
    }
};

template<typename SAX, typename LexerType = void>
struct sax_call_null_function : sax_call_function<
        sax_call_null_function<SAX, LexerType>, 
        SAX, LexerType>
{
    template<typename T, typename...Ts>
    using call_base_t = decltype(std::declval<T&>().null(std::declval<Ts>()...));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().null(std::declval<std::size_t>())); // remove

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().null(*std::declval<const LexerType*>())); // remove

    template<typename...Ts>
    static bool do_call(SAX* sax, Ts&&...ts)
    {
        return sax->null(std::forward<Ts>(ts)...);
    }
};

template<typename SAX, typename LexerType = void>
struct sax_call_boolean_function : sax_call_function<
        sax_call_boolean_function<SAX, LexerType>, 
        SAX, LexerType, bool>
{
    template<typename T, typename...Ts>
    using call_base_t = decltype(std::declval<T&>().boolean(std::declval<bool>(), std::declval<Ts>()...));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().boolean(std::declval<bool>(), std::declval<std::size_t>())); // remove

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().boolean(std::declval<bool>(), *std::declval<const LexerType*>())); // remove
    
    template<typename...Ts>
    static bool do_call(SAX* sax, Ts&&...ts)
    {
        return sax->boolean(std::forward<Ts>(ts)...);
    }
};

template<typename SAX, typename Integer, typename LexerType = void>
struct sax_call_number_integer_function : sax_call_function<
        sax_call_number_integer_function<SAX, Integer, LexerType>, 
        SAX, LexerType, Integer>
{
    template<typename T, typename...Ts>
    using call_base_t = decltype(std::declval<T&>().number_integer(std::declval<Integer>(), std::declval<Ts>()...));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().number_integer(std::declval<Integer>(), std::declval<std::size_t>())); // remove

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().number_integer(std::declval<Integer>(), *std::declval<const LexerType*>())); // remove
             
    template<typename...Ts >
    static bool do_call(SAX* sax, Ts&&...ts)
    {
        return sax->number_integer(std::forward<Ts>(ts)...);
    }
};

template<typename SAX, typename Unsigned, typename LexerType = void>
struct sax_call_number_unsigned_function : sax_call_function<
        sax_call_number_unsigned_function<SAX, Unsigned, LexerType>, 
        SAX, LexerType, Unsigned>
{
    template<typename T, typename...Ts>
    using call_base_t = decltype(std::declval<T&>().number_unsigned(std::declval<Unsigned>(), std::declval<Ts>()...));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().number_unsigned(std::declval<Unsigned>(), std::declval<std::size_t>())); // remove

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().number_unsigned(std::declval<Unsigned>(), *std::declval<const LexerType*>())); // remove
                      
    template<typename...Ts>
    static bool do_call(SAX* sax, Ts&&...ts)
    {
        return sax->number_unsigned(std::forward<Ts>(ts)...);
    }
};

template<typename SAX, typename Float, typename String, typename LexerType = void>
struct sax_call_number_float_function : sax_call_function<
        sax_call_number_float_function<SAX, Float, String, LexerType>, 
        SAX, LexerType, Float, String>
{
    template<typename T, typename...Ts>
    using call_base_t = decltype(std::declval<T&>().number_float(std::declval<Float>(), std::declval<String>(), std::declval<Ts>()...));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().number_float(std::declval<Float>(), std::declval<String>(), std::declval<std::size_t>())); // remove

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().number_float(std::declval<Float>(), std::declval<String>(), *std::declval<const LexerType*>())); // remove
                               
    template<typename...Ts> 
    static bool do_call(SAX* sax, Ts&&...ts)
    {
        return sax->number_float(std::forward<Ts>(ts)...);
    }
};

template<typename SAX, typename String, typename LexerType = void>
struct sax_call_string_function : sax_call_function<
        sax_call_string_function<SAX, String, LexerType>, 
        SAX, LexerType, String>
{
    template<typename T, typename...Ts>
    using call_base_t = decltype(std::declval<T&>().string(std::declval<String>(), std::declval<Ts>()...));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().string(std::declval<String>(), std::declval<std::size_t>())); // remove

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().string(std::declval<String>(), *std::declval<const LexerType*>())); // remove
                               
    template<typename...Ts> 
    static bool do_call(SAX* sax, Ts&&...ts)
    {
        return sax->string(std::forward<Ts>(ts)...);
    }
};

template<typename SAX, typename Binary, typename LexerType = void>
struct sax_call_binary_function : sax_call_function<
        sax_call_binary_function<SAX, Binary, LexerType>, 
        SAX, LexerType, Binary>
{
    template<typename T, typename...Ts>
    using call_base_t = decltype(std::declval<T&>().binary(std::declval<Binary>(), std::declval<Ts>()...));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().binary(std::declval<Binary>(), std::declval<std::size_t>())); // remove

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().binary(std::declval<Binary>(), *std::declval<const LexerType*>())); // remove
    
    template<typename...Ts> 
    static bool do_call(SAX* sax, Ts&&...ts)
    {
        return sax->binary(std::forward<Ts>(ts)...);
    }
};

template<typename SAX, typename LexerType = void>
struct sax_call_start_object_function : sax_call_function<
        sax_call_start_object_function<SAX, LexerType>, 
        SAX, LexerType, std::size_t>
{
    template<typename T, typename...Ts>
    using call_base_t = decltype(std::declval<T&>().start_object(std::declval<std::size_t>(), std::declval<Ts>()...));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().start_object(std::declval<std::size_t>(), std::declval<std::size_t>())); // remove

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().start_object(std::declval<std::size_t>(), *std::declval<const LexerType*>())); // remove
    
    template<typename...Ts> 
    static bool do_call(SAX* sax, Ts&&...ts)
    {
        return sax->start_object(std::forward<Ts>(ts)...);
    }
};

template<typename SAX, typename String, typename LexerType = void>
struct sax_call_key_function : sax_call_function<
        sax_call_key_function<SAX, String, LexerType>, 
        SAX, LexerType, String>
{
    template<typename T, typename...Ts>
    using call_base_t = decltype(std::declval<T&>().key(std::declval<String>(), std::declval<Ts>()...));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().key(std::declval<String>(), std::declval<std::size_t>())); // remove

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().key(std::declval<String>(), *std::declval<const LexerType*>())); // remove
    
    template<typename...Ts> 
    static bool do_call(SAX* sax, Ts&&...ts)
    {
        return sax->key(std::forward<Ts>(ts)...);
    }
};

template<typename SAX, typename LexerType = void>
struct sax_call_end_object_function : sax_call_function<
        sax_call_end_object_function<SAX, LexerType>, 
        SAX, LexerType>
{
    template<typename T, typename...Ts>
    using call_base_t = decltype(std::declval<T&>().end_object(std::declval<Ts>()...));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().end_object(std::declval<std::size_t>())); // remove

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().end_object(*std::declval<const LexerType*>())); // remove
    
    template<typename...Ts> 
    static bool do_call(SAX* sax, Ts&&...ts)
    {
        return sax->end_object(std::forward<Ts>(ts)...);
    }
};

template<typename SAX, typename LexerType = void>
struct sax_call_start_array_function : sax_call_function<
        sax_call_start_array_function<SAX, LexerType>, 
        SAX, LexerType, std::size_t>
{
    template<typename T, typename...Ts>
    using call_base_t = decltype(std::declval<T&>().start_array(std::declval<std::size_t>(), std::declval<Ts>()...));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().start_array(std::declval<std::size_t>(), std::declval<std::size_t>())); // remove

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().start_array(std::declval<std::size_t>(), *std::declval<const LexerType*>())); // remove
    
    template<typename...Ts> 
    static bool do_call(SAX* sax, Ts&&...ts)
    {
        return sax->start_array(std::forward<Ts>(ts)...);
    }
};

template<typename SAX, typename LexerType = void>
struct sax_call_end_array_function : sax_call_function<
        sax_call_end_array_function<SAX, LexerType>, 
        SAX, LexerType>
{
    template<typename T, typename...Ts>
    using call_base_t = decltype(std::declval<T&>().end_array(std::declval<Ts>()...));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().end_array(std::declval<std::size_t>())); // remove

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().end_array(*std::declval<const LexerType*>())); // remove
    
    template<typename...Ts> 
    static bool do_call(SAX* sax, Ts&&...ts)
    {
        return sax->end_array(std::forward<Ts>(ts)...);
    }
};

template<typename T, typename Exception>
using parse_error_function_t = decltype(std::declval<T&>().parse_error(
        std::declval<std::size_t>(), std::declval<const std::string&>(),
        std::declval<const Exception&>()));

template<typename SAX, typename BasicJsonType, typename LexerType = void>
struct is_sax
{
  private:
    static_assert(is_basic_json<BasicJsonType>::value,
                  "BasicJsonType must be of type basic_json<...>");

    using number_integer_t = typename BasicJsonType::number_integer_t;
    using number_unsigned_t = typename BasicJsonType::number_unsigned_t;
    using number_float_t = typename BasicJsonType::number_float_t;
    using string_t = typename BasicJsonType::string_t;
    using binary_t = typename BasicJsonType::binary_t;
    using exception_t = typename BasicJsonType::exception;

  public:
    static constexpr bool value =
        sax_call_null_function<SAX, LexerType>::valid &&
        sax_call_boolean_function<SAX, LexerType>::valid &&
        sax_call_number_integer_function<SAX, number_integer_t, LexerType>::valid &&
        sax_call_number_unsigned_function<SAX, number_unsigned_t, LexerType>::valid &&
        sax_call_number_float_function<SAX, number_float_t, const string_t&, LexerType>::valid &&
        sax_call_string_function<SAX, string_t&, LexerType>::valid &&
        sax_call_binary_function<SAX, binary_t&, LexerType>::valid &&
        sax_call_start_object_function<SAX, LexerType>::valid &&
        sax_call_key_function<SAX, string_t&, LexerType>::valid &&
        sax_call_end_object_function<SAX, LexerType>::valid &&
        sax_call_start_array_function<SAX, LexerType>::valid &&
        sax_call_end_array_function<SAX, LexerType>::valid &&
        is_detected_exact<bool, parse_error_function_t, SAX, exception_t>::value;
};

template<typename SAX, typename BasicJsonType, typename LexerType = void>
struct is_sax_static_asserts
{
  private:
    static_assert(is_basic_json<BasicJsonType>::value,
                  "BasicJsonType must be of type basic_json<...>");

    using number_integer_t = typename BasicJsonType::number_integer_t;
    using number_unsigned_t = typename BasicJsonType::number_unsigned_t;
    using number_float_t = typename BasicJsonType::number_float_t;
    using string_t = typename BasicJsonType::string_t;
    using binary_t = typename BasicJsonType::binary_t;
    using exception_t = typename BasicJsonType::exception;

  public:
    static_assert(sax_call_null_function<SAX, LexerType>::valid,
                  "Missing/invalid function: "
                  "'bool null()' or "
                  "'bool null(std::size_t)' or "
                  "'bool null(lexer_t)'");
    static_assert(sax_call_boolean_function<SAX, LexerType>::valid,
                  "Missing/invalid function: "
                  "'bool boolean(bool)' or "
                  "'bool boolean(bool, std::size_t)' or "
                  "'bool boolean(bool, lexer_t)'");
    static_assert(
        sax_call_number_integer_function<SAX, number_integer_t, LexerType>::valid,
        "Missing/invalid function: "
        "'bool number_integer(number_integer_t)' or "
        "'bool number_integer(number_integer_t, std::size_t)' or "
        "'bool number_integer(number_integer_t, lexer_t)'");
    static_assert(
        sax_call_number_unsigned_function<SAX, number_unsigned_t, LexerType>::valid,
        "Missing/invalid function: "
        "'bool number_unsigned(number_unsigned_t)' or "
        "'bool number_unsigned(number_unsigned_t, std::size_t)' or "
        "'bool number_unsigned(number_unsigned_t, lexer_t)'");
    static_assert(
        sax_call_number_float_function<SAX, number_float_t, const string_t&, LexerType>::valid,
        "Missing/invalid function:)"
        "'bool number_float(number_float_t, const string_t&)' or "
        "'bool number_float(number_float_t, const string_t&, std::size_t)' or "
        "'bool number_float(number_float_t, const string_t&, lexer_t)'");
    static_assert(
        sax_call_string_function<SAX, string_t&, LexerType>::valid,
        "Missing/invalid function: "
        "'bool string(string_t&)' or "
        "'bool string(string_t&, std::size_t)' or "
        "'bool string(string_t&, lexer_t)'");
    static_assert(
        sax_call_binary_function<SAX, binary_t&, LexerType>::valid,
        "Missing/invalid function: "
        "'bool binary(binary_t&)' or "
        "'bool binary(binary_t&, std::size_t)' or "
        "'bool binary(binary_t&, lexer_t)'");
    static_assert(sax_call_start_object_function<SAX, LexerType>::valid,
                  "Missing/invalid function: "
                  "'bool start_object(std::size_t)' or "
                  "'bool start_object(std::size_t, std::size_t)' or "
                  "'bool start_object(std::size_t, lexer_t)'");
    static_assert(sax_call_key_function<SAX, string_t&, LexerType>::valid,
                  "Missing/invalid function: "
                  "'bool key(string_t&)' or "
                  "'bool key(string_t&, std::size_t)' or "
                  "'bool key(string_t&, lexer_t)'");
    static_assert(sax_call_end_object_function<SAX, LexerType>::valid,
                  "Missing/invalid function: "
                  "'bool end_object()' or "
                  "'bool end_object(std::size_t)' or "
                  "'bool end_object(lexer_t)'");
    static_assert(sax_call_start_array_function<SAX, LexerType>::valid,
                  "Missing/invalid function: "
                  "'bool start_array(std::size_t)' or "
                  "'bool start_array(std::size_t, std::size_t)' or "
                  "'bool start_array(std::size_t, lexer_t)'");
    static_assert(sax_call_end_array_function<SAX, LexerType>::valid,
                  "Missing/invalid function: bool end_array()"
                  "'bool bool end_array()' or "
                  "'bool bool end_array(std::size_t)' or "
                  "'bool bool end_array(lexer_t)'");
    static_assert(
        is_detected_exact<bool, parse_error_function_t, SAX, exception_t>::value,
        "Missing/invalid function: bool parse_error(std::size_t, const "
        "std::string&, const exception&)");
};
}  // namespace detail
}  // namespace nlohmann
