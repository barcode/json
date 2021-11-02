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
    template<typename...> typename DerivedTempl,
    typename SAX,
    typename LexerType,
    typename...Ts >
struct sax_call_function
{
    using Derived = DerivedTempl<SAX, Ts..., LexerType>;

    static constexpr bool no_lexer = std::is_same<LexerType, void>::value;

    static constexpr bool detected_call_base =
        is_detected_exact<bool, Derived::template call_base_t, SAX>::value;

    static constexpr bool detected_call_with_pos =
        is_detected_exact<bool, Derived::template call_with_pos_t, SAX>::value;

    static constexpr bool detected_call_with_lex =
        !no_lexer &&
        is_detected_exact<bool, Derived::template call_with_lex_t, SAX>::value;

    static constexpr bool valid =
        detected_call_base ||
        detected_call_with_pos ||
        detected_call_with_lex;
};

template<typename SAX, typename LexerType = void>
struct sax_call_null_function : sax_call_function<sax_call_null_function, SAX, LexerType>
{
    template<typename T>
    using call_base_t = decltype(std::declval<T&>().null());

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().null(std::declval<std::size_t>()));

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().null(*std::declval<const LexerType*>()));

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    sax_call_null_function<SaxT, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, std::size_t pos)
    {
        return sax->null(pos);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_null_function<SaxT, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, std::size_t pos)
    {
        return sax->null();
    }
    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_null_function<SaxT, LexT>::no_lexer &&
    sax_call_null_function<SaxT, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, const LexT& lex)
    {
        return sax->null(lex);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_null_function<SaxT, LexT>::no_lexer &&
    !sax_call_null_function<SaxT, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, const LexT& lex)
    {
        return call(sax, lex.get_position().chars_read_total);
    }
};

template<typename SAX, typename LexerType = void>
struct sax_call_boolean_function : sax_call_function<sax_call_boolean_function, SAX, LexerType>
{
    template<typename T>
    using call_base_t = decltype(std::declval<T&>().boolean(std::declval<bool>()));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().boolean(std::declval<bool>(), std::declval<std::size_t>()));

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().boolean(std::declval<bool>(), *std::declval<const LexerType*>()));

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    sax_call_boolean_function<SaxT, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, bool val, std::size_t pos)
    {
        return sax->boolean(val, pos);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_boolean_function<SaxT, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, bool val, std::size_t pos)
    {
        return sax->boolean(val);
    }
    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_boolean_function<SaxT, LexT>::no_lexer &&
    sax_call_boolean_function<SaxT, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, bool val, const LexT& lex)
    {
        return sax->boolean(val, lex);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_boolean_function<SaxT, LexT>::no_lexer &&
    !sax_call_boolean_function<SaxT, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, bool val, const LexT& lex)
    {
        return call(sax, val, lex.get_position().chars_read_total);
    }
};

template<typename SAX, typename Integer, typename LexerType = void>
struct sax_call_number_integer_function : sax_call_function<sax_call_number_integer_function, SAX, LexerType, Integer>
{
    template<typename T>
    using call_base_t = decltype(std::declval<T&>().number_integer(std::declval<Integer>()));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().number_integer(std::declval<Integer>(), std::declval<std::size_t>()));

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().number_integer(std::declval<Integer>(), *std::declval<const LexerType*>()));

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    sax_call_number_integer_function<SaxT, Integer, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, Integer val, std::size_t pos)
    {
        return sax->number_integer(val, pos);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_number_integer_function<SaxT, Integer, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, Integer val, std::size_t pos)
    {
        return sax->number_integer(val);
    }
    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_number_integer_function<SaxT, Integer, LexT>::no_lexer &&
    sax_call_number_integer_function<SaxT, Integer, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, Integer val, const LexT& lex)
    {
        return sax->number_integer(val, lex);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_number_integer_function<SaxT, Integer, LexT>::no_lexer &&
    !sax_call_number_integer_function<SaxT, Integer, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, Integer val, const LexT& lex)
    {
        return call(sax, val, lex.get_position().chars_read_total);
    }
};

template<typename SAX, typename Unsigned, typename LexerType = void>
struct sax_call_number_unsigned_function : sax_call_function<sax_call_number_unsigned_function, SAX, LexerType, Unsigned>
{
    template<typename T>
    using call_base_t = decltype(std::declval<T&>().number_unsigned(std::declval<Unsigned>()));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().number_unsigned(std::declval<Unsigned>(), std::declval<std::size_t>()));

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().number_unsigned(std::declval<Unsigned>(), *std::declval<const LexerType*>()));

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    sax_call_number_unsigned_function<SaxT, Unsigned, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, Unsigned val, std::size_t pos)
    {
        return sax->number_unsigned(val, pos);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_number_unsigned_function<SaxT, Unsigned, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, Unsigned val, std::size_t pos)
    {
        return sax->number_unsigned(val);
    }
    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_number_unsigned_function<SaxT, Unsigned, LexT>::no_lexer &&
    sax_call_number_unsigned_function<SaxT, Unsigned, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, Unsigned val, const LexT& lex)
    {
        return sax->number_unsigned(val, lex);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_number_unsigned_function<SaxT, Unsigned, LexT>::no_lexer &&
    !sax_call_number_unsigned_function<SaxT, Unsigned, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, Unsigned val, const LexT& lex)
    {
        return call(sax, val, lex.get_position().chars_read_total);
    }
};

template<typename SAX, typename Float, typename String, typename LexerType = void>
struct sax_call_number_float_function : sax_call_function<sax_call_number_float_function, SAX, LexerType, Float, String>
{
    template<typename T>
    using call_base_t = decltype(std::declval<T&>().number_float(std::declval<Float>(), std::declval<const String&>()));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().number_float(std::declval<Float>(), std::declval<const String&>(), std::declval<std::size_t>()));

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().number_float(std::declval<Float>(), std::declval<const String&>(), *std::declval<const LexerType*>()));

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    sax_call_number_float_function<SaxT, Float, String, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, Float val, const String& str, std::size_t pos)
    {
        return sax->number_float(val, str, pos);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_number_float_function<SaxT, Float, String, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, Float val, const String& str, std::size_t pos)
    {
        return sax->number_float(val, str);
    }
    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_number_float_function<SaxT, Float, String, LexT>::no_lexer &&
    sax_call_number_float_function<SaxT, Float, String, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, Float val, const String& str, const LexT& lex)
    {
        return sax->number_float(val, str, lex);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_number_float_function<SaxT, Float, String, LexT>::no_lexer &&
    !sax_call_number_float_function<SaxT, Float, String, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, Float val, const String& str, const LexT& lex)
    {
        return call(sax, val, str, lex.get_position().chars_read_total);
    }
};

template<typename SAX, typename String, typename LexerType = void>
struct sax_call_string_function : sax_call_function<sax_call_string_function, SAX, LexerType, String>
{
    template<typename T>
    using call_base_t = decltype(std::declval<T&>().string(std::declval<String&>()));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().string(std::declval<String&>(), std::declval<std::size_t>()));

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().string(std::declval<String&>(), *std::declval<const LexerType*>()));

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    sax_call_string_function<SaxT, String, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, String& val, std::size_t pos)
    {
        return sax->string(val, pos);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_string_function<SaxT, String, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, String& val, std::size_t pos)
    {
        return sax->string(val);
    }
    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_string_function<SaxT, String, LexT>::no_lexer &&
    sax_call_string_function<SaxT, String, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, String& val, const LexT& lex)
    {
        return sax->string(val, lex);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_string_function<SaxT, String, LexT>::no_lexer &&
    !sax_call_string_function<SaxT, String, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, String& val, const LexT& lex)
    {
        return call(sax, val, lex.get_position().chars_read_total);
    }
};

template<typename SAX, typename Binary, typename LexerType = void>
struct sax_call_binary_function : sax_call_function<sax_call_binary_function, SAX, LexerType, Binary>
{
    template<typename T>
    using call_base_t = decltype(std::declval<T&>().binary(std::declval<Binary&>()));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().binary(std::declval<Binary&>(), std::declval<std::size_t>()));

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().binary(std::declval<Binary&>(), *std::declval<const LexerType*>()));

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    sax_call_binary_function<SaxT, Binary, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, Binary& val, std::size_t pos)
    {
        return sax->binary(val, pos);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_binary_function<SaxT, Binary, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, Binary& val, std::size_t pos)
    {
        return sax->binary(val);
    }
    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_binary_function<SaxT, Binary, LexT>::no_lexer &&
    sax_call_binary_function<SaxT, Binary, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, Binary& val, const LexT& lex)
    {
        return sax->binary(val, lex);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_binary_function<SaxT, Binary, LexT>::no_lexer &&
    !sax_call_binary_function<SaxT, Binary, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, Binary& val, const LexT& lex)
    {
        return call(sax, val, lex.get_position().chars_read_total);
    }
};

template<typename SAX, typename LexerType = void>
struct sax_call_start_object_function : sax_call_function<sax_call_start_object_function, SAX, LexerType>
{
    template<typename T>
    using call_base_t = decltype(std::declval<T&>().start_object(std::declval<std::size_t>()));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().start_object(std::declval<std::size_t>(), std::declval<std::size_t>()));

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().start_object(std::declval<std::size_t>(), *std::declval<const LexerType*>()));

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    sax_call_start_object_function<SaxT, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, std::size_t len, std::size_t pos)
    {
        return sax->start_object(len, pos);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_start_object_function<SaxT, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, std::size_t len, std::size_t pos)
    {
        return sax->start_object(len);
    }
    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_start_object_function<SaxT, LexT>::no_lexer &&
    sax_call_start_object_function<SaxT, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, std::size_t len, const LexT& lex)
    {
        return sax->start_object(len, lex);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_start_object_function<SaxT, LexT>::no_lexer &&
    !sax_call_start_object_function<SaxT, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, std::size_t len, const LexT& lex)
    {
        return call(sax, len, lex.get_position().chars_read_total);
    }
};

template<typename SAX, typename String, typename LexerType = void>
struct sax_call_key_function : sax_call_function<sax_call_key_function, SAX, LexerType, String>
{
    template<typename T>
    using call_base_t = decltype(std::declval<T&>().key(std::declval<String&>()));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().key(std::declval<String&>(), std::declval<std::size_t>()));

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().key(std::declval<String&>(), *std::declval<const LexerType*>()));

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    sax_call_key_function<SaxT, String, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, String& val, std::size_t pos)
    {
        return sax->key(val, pos);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_key_function<SaxT, String, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, String& val, std::size_t pos)
    {
        return sax->key(val);
    }
    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_key_function<SaxT, String, LexT>::no_lexer &&
    sax_call_key_function<SaxT, String, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, String& val, const LexT& lex)
    {
        return sax->key(val, lex);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_key_function<SaxT, String, LexT>::no_lexer &&
    !sax_call_key_function<SaxT, String, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, String& val, const LexT& lex)
    {
        return call(sax, val, lex.get_position().chars_read_total);
    }
};

template<typename SAX, typename LexerType = void>
struct sax_call_end_object_function : sax_call_function<sax_call_end_object_function, SAX, LexerType>
{
    template<typename T>
    using call_base_t = decltype(std::declval<T&>().end_object());

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().end_object(std::declval<std::size_t>()));

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().end_object(*std::declval<const LexerType*>()));

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    sax_call_end_object_function<SaxT, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, std::size_t pos)
    {
        return sax->end_object(pos);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_end_object_function<SaxT, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, std::size_t pos)
    {
        return sax->end_object();
    }
    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_end_object_function<SaxT, LexT>::no_lexer &&
    sax_call_end_object_function<SaxT, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, const LexT& lex)
    {
        return sax->end_object(lex);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_end_object_function<SaxT, LexT>::no_lexer &&
    !sax_call_end_object_function<SaxT, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, const LexT& lex)
    {
        return call(sax, lex.get_position().chars_read_total);
    }
};

template<typename SAX, typename LexerType = void>
struct sax_call_start_array_function : sax_call_function<sax_call_start_array_function, SAX, LexerType>
{
    template<typename T>
    using call_base_t = decltype(std::declval<T&>().start_array(std::declval<std::size_t>()));

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().start_array(std::declval<std::size_t>(), std::declval<std::size_t>()));

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().start_array(std::declval<std::size_t>(), *std::declval<const LexerType*>()));

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    sax_call_start_array_function<SaxT, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, std::size_t len, std::size_t pos)
    {
        return sax->start_array(len, pos);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_start_array_function<SaxT, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, std::size_t len, std::size_t pos)
    {
        return sax->start_array(len);
    }
    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_start_array_function<SaxT, LexT>::no_lexer &&
    sax_call_start_array_function<SaxT, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, std::size_t len, const LexT& lex)
    {
        return sax->start_array(len, lex);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_start_array_function<SaxT, LexT>::no_lexer &&
    !sax_call_start_array_function<SaxT, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, std::size_t len, const LexT& lex)
    {
        return call(sax, len, lex.get_position().chars_read_total);
    }
};

template<typename SAX, typename LexerType = void>
struct sax_call_end_array_function : sax_call_function<sax_call_end_array_function, SAX, LexerType>
{
    template<typename T>
    using call_base_t = decltype(std::declval<T&>().end_array());

    template<typename T>
    using call_with_pos_t = decltype(std::declval<T&>().end_array(std::declval<std::size_t>()));

    template<typename T>
    using call_with_lex_t = decltype(std::declval<T&>().end_array(*std::declval<const LexerType*>()));

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    sax_call_end_array_function<SaxT, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, std::size_t pos)
    {
        return sax->end_array(pos);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_end_array_function<SaxT, LexT>::detected_call_with_pos
    , bool >::type
    call(SaxT* sax, std::size_t pos)
    {
        return sax->end_array();
    }
    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_end_array_function<SaxT, LexT>::no_lexer &&
    sax_call_end_array_function<SaxT, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, const LexT& lex)
    {
        return sax->end_array(lex);
    }

    template<typename SaxT = SAX, typename LexT = LexerType>
    static typename std::enable_if <
    !sax_call_end_array_function<SaxT, LexT>::no_lexer &&
    !sax_call_end_array_function<SaxT, LexT>::detected_call_with_lex
    , bool >::type
    call(SaxT* sax, const LexT& lex)
    {
        return call(sax, lex.get_position().chars_read_total);
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
        sax_call_number_float_function<SAX, number_float_t, string_t, LexerType>::valid &&
        sax_call_string_function<SAX, string_t, LexerType>::valid &&
        sax_call_binary_function<SAX, binary_t, LexerType>::valid &&
        sax_call_start_object_function<SAX, LexerType>::valid &&
        sax_call_key_function<SAX, string_t, LexerType>::valid &&
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
        sax_call_number_float_function<SAX, number_float_t, string_t, LexerType>::valid,
        "Missing/invalid function:)"
        "'bool number_float(number_float_t, const string_t&)' or "
        "'bool number_float(number_float_t, const string_t&, std::size_t)' or "
        "'bool number_float(number_float_t, const string_t&, lexer_t)'");
    static_assert(
        sax_call_string_function<SAX, string_t, LexerType>::valid,
        "Missing/invalid function: "
        "'bool string(string_t&)' or "
        "'bool string(string_t&, std::size_t)' or "
        "'bool string(string_t&, lexer_t)'");
    static_assert(
        sax_call_binary_function<SAX, binary_t, LexerType>::valid,
        "Missing/invalid function: "
        "'bool binary(binary_t&)' or "
        "'bool binary(binary_t&, std::size_t)' or "
        "'bool binary(binary_t&, lexer_t)'");
    static_assert(sax_call_start_object_function<SAX, LexerType>::valid,
                  "Missing/invalid function: "
                  "'bool start_object(std::size_t)' or "
                  "'bool start_object(std::size_t, std::size_t)' or "
                  "'bool start_object(std::size_t, lexer_t)'");
    static_assert(sax_call_key_function<SAX, string_t, LexerType>::valid,
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
