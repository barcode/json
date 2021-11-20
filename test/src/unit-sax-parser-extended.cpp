/*
    __ _____ _____ _____
 __|  |   __|     |   | |  JSON for Modern C++ (test suite)
|  |  |__   |  |  | | | |  version 3.10.2
|_____|_____|_____|_|___|  https://github.com/nlohmann/json

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
SPDX-License-Identifier: MIT
Copyright (c) 2013-2019 Niels Lohmann <http://nlohmann.me>.

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <set>
#include <sstream>
#include <string>
#include <type_traits>

#include "doctest_compatibility.h"

#include <nlohmann/json.hpp>

// ???????
template <bool LexCallImpossible, bool WithPos, bool WithLex>
struct Sax
{
    using json = nlohmann::json;

    bool null()
    {
        CHECK(!WithPos);
        CHECK((!WithLex || LexCallImpossible));
        return true;
    }
    template<bool Act = WithPos>
    typename std::enable_if<Act, bool>::type null(std::size_t pos)
    {
        CHECK((!WithLex || LexCallImpossible));
        INFO("pos = " << pos);
        CHECK(1 == pos_null.count(pos));
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type null(const LexT& lex)
    {
        CHECK(1 == pos_null.count(lex.get_position().chars_read_total));
        return true;
    }

    bool boolean(bool /*unused*/)
    {
        CHECK(!WithPos);
        CHECK((!WithLex || LexCallImpossible));
        return true;
    }
    template<bool Act = WithPos>
    typename std::enable_if<Act, bool>::type boolean(bool /*unused*/, std::size_t pos)
    {
        CHECK((!WithLex || LexCallImpossible));
        INFO("pos = " << pos);
        CHECK(1 == pos_boolean.count(pos));
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type boolean(bool /*unused*/, const LexT& lex)
    {
        CHECK(1 == pos_boolean.count(lex.get_position().chars_read_total));
        return true;
    }

    bool number_integer(json::number_integer_t /*unused*/)
    {
        CHECK(!WithPos);
        CHECK((!WithLex || LexCallImpossible));
        return true;
    }
    template<bool Act = WithPos>
    typename std::enable_if<Act, bool>::type number_integer(json::number_integer_t /*unused*/, std::size_t pos)
    {
        CHECK((!WithLex || LexCallImpossible));
        INFO("pos = " << pos);
        CHECK(1 == pos_number_integer.count(pos));
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type number_integer(json::number_integer_t /*unused*/, const LexT& lex)
    {
        CHECK(1 == pos_number_integer.count(lex.get_position().chars_read_total));
        return true;
    }

    bool number_unsigned(json::number_unsigned_t /*unused*/)
    {
        CHECK(!WithPos);
        CHECK((!WithLex || LexCallImpossible));
        return true;
    }
    template<bool Act = WithPos>
    typename std::enable_if<Act, bool>::type number_unsigned(json::number_unsigned_t /*unused*/, std::size_t pos)
    {
        CHECK((!WithLex || LexCallImpossible));
        INFO("pos = " << pos);
        CHECK(1 == pos_number_unsigned.count(pos));
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type number_unsigned(json::number_unsigned_t /*unused*/, const LexT& lex)
    {
        CHECK(1 == pos_number_unsigned.count(lex.get_position().chars_read_total));
        return true;
    }

    bool number_float(json::number_float_t /*unused*/, const std::string& /*unused*/)
    {
        CHECK(!WithPos);
        CHECK((!WithLex || LexCallImpossible));
        return true;
    }
    template<bool Act = WithPos>
    typename std::enable_if<Act, bool>::type number_float(json::number_float_t /*unused*/, const std::string& /*unused*/, std::size_t pos)
    {
        CHECK((!WithLex || LexCallImpossible));
        INFO("pos = " << pos);
        CHECK(1 == pos_number_float.count(pos));
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type number_float(json::number_float_t /*unused*/, const std::string& /*unused*/, const LexT& lex)
    {
        CHECK(1 == pos_number_float.count(lex.get_position().chars_read_total));
        return true;
    }

    bool string(std::string& /*unused*/)
    {
        CHECK(!WithPos);
        CHECK((!WithLex || LexCallImpossible));
        return true;
    }
    template<bool Act = WithPos>
    typename std::enable_if<Act, bool>::type string(std::string& /*unused*/, std::size_t pos)
    {
        CHECK((!WithLex || LexCallImpossible));
        INFO("pos = " << pos);
        CHECK(1 == pos_string.count(pos));
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type string(std::string& /*unused*/, const LexT& lex)
    {
        CHECK(1 == pos_string.count(lex.get_position().chars_read_total));
        return true;
    }

    bool binary(std::vector<std::uint8_t>& /*unused*/)
    {
        CHECK(!WithPos);
        CHECK((!WithLex || LexCallImpossible));
        return true;
    }
    template<bool Act = WithPos>
    typename std::enable_if<Act, bool>::type binary(std::vector<std::uint8_t>& /*unused*/, std::size_t pos)
    {
        CHECK((!WithLex || LexCallImpossible));
        INFO("pos = " << pos);
        CHECK(1 == pos_binary.count(pos));
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type binary(std::vector<std::uint8_t>& /*unused*/, const LexT& lex)
    {
        CHECK(1 == pos_binary.count(lex.get_position().chars_read_total));
        return true;
    }

    bool start_object(std::size_t /*unused*/)
    {
        CHECK(!WithPos);
        CHECK((!WithLex || LexCallImpossible));
        return true;
    }
    template<bool Act = WithPos>
    typename std::enable_if<Act, bool>::type start_object(std::size_t /*unused*/, long unsigned int pos)
    {
        CHECK((!WithLex || LexCallImpossible));
        INFO("pos = " << pos);
        CHECK(1 == pos_start_object.count(pos));
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type start_object(std::size_t /*unused*/, const LexT& lex)
    {
        CHECK(1 == pos_start_object.count(lex.get_position().chars_read_total));
        return true;
    }

    bool key(std::string& /*unused*/)
    {
        CHECK(!WithPos);
        CHECK((!WithLex || LexCallImpossible));
        return true;
    }
    template<bool Act = WithPos>
    typename std::enable_if<Act, bool>::type key(std::string& /*unused*/, std::size_t pos)
    {
        CHECK((!WithLex || LexCallImpossible));
        INFO("pos = " << pos);
        CHECK(1 == pos_key.count(pos));
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type key(std::string& /*unused*/, const LexT& lex)
    {
        CHECK(1 == pos_key.count(lex.get_position().chars_read_total));
        return true;
    }

    bool end_object()
    {
        CHECK(!WithPos);
        CHECK((!WithLex || LexCallImpossible));
        return true;
    }
    template<bool Act = WithPos>
    typename std::enable_if<Act, bool>::type end_object(std::size_t pos)
    {
        CHECK((!WithLex || LexCallImpossible));
        INFO("pos = " << pos);
        CHECK(1 == pos_end_object.count(pos));
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type end_object(const LexT& lex)
    {
        CHECK(1 == pos_end_object.count(lex.get_position().chars_read_total));
        return true;
    }

    bool start_array(std::size_t /*unused*/)
    {
        CHECK(!WithPos);
        CHECK((!WithLex || LexCallImpossible));
        return true;
    }
    template<bool Act = WithPos>
    typename std::enable_if<Act, bool>::type start_array(std::size_t /*unused*/, std::size_t pos)
    {
        CHECK((!WithLex || LexCallImpossible));
        INFO("pos = " << pos);
        CHECK(1 == pos_start_array.count(pos));
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type start_array(std::size_t /*unused*/, const LexT& lex)
    {
        CHECK(1 == pos_start_array.count(lex.get_position().chars_read_total));
        return true;
    }

    bool end_array()
    {
        CHECK(!WithPos);
        CHECK((!WithLex || LexCallImpossible));
        return true;
    }
    template<bool Act = WithPos>
    typename std::enable_if<Act, bool>::type end_array(std::size_t pos)
    {
        CHECK((!WithLex || LexCallImpossible));
        INFO("pos = " << pos);
        CHECK(1 == pos_end_array.count(pos));
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type end_array(const LexT& lex)
    {
        CHECK(1 == pos_end_array.count(lex.get_position().chars_read_total));
        return true;
    }

    bool parse_error(std::size_t /*unused*/, const std::string& /*unused*/, const json::exception& /*unused*/) // NOLINT(readability-convert-member-functions-to-static)
    {
        return false;
    }
    
    std::set<std::size_t> pos_null;
    std::set<std::size_t> pos_boolean;
    std::set<std::size_t> pos_number_integer;
    std::set<std::size_t> pos_number_unsigned;
    std::set<std::size_t> pos_number_float;
    std::set<std::size_t> pos_string;
    std::set<std::size_t> pos_binary;
    std::set<std::size_t> pos_start_object;
    std::set<std::size_t> pos_key;
    std::set<std::size_t> pos_end_object;
    std::set<std::size_t> pos_start_array;
    std::set<std::size_t> pos_end_array;
};

template<bool WithPosV, bool WithLexV>
struct Opt
{
    static constexpr bool WithPos = WithPosV;
    static constexpr bool WithLex = WithLexV;
};

using OptNone = Opt<0, 0>;
using OptLex = Opt<0, 1>;
using OptPos = Opt<1, 0>;
using OptBoth = Opt<1, 1>;

TEST_CASE_TEMPLATE("extended parser", T, OptNone, OptLex, OptPos, OptBoth )
{
    INFO("WithPos " << T::WithPos << ", WithLex " << T::WithLex);
    const std::string str = R"({"array" : [123456789,-1,true,4.2,null,"str"]})";
    SECTION("json")
    {
        Sax</*LexCallImpossible*/ false, T::WithPos, T::WithLex> sax;
        sax.pos_start_object.emplace(1);
        sax.pos_key.emplace(8);
        sax.pos_start_array.emplace(12);
        sax.pos_number_unsigned.emplace(21);
        sax.pos_number_integer.emplace(24);
        sax.pos_boolean.emplace(29);
        sax.pos_number_float.emplace(33);
        sax.pos_null.emplace(38);
        sax.pos_string.emplace(44);
        sax.pos_end_array.emplace(45);
        sax.pos_end_object.emplace(46);
        CHECK(nlohmann::json::sax_parse(str, &sax, nlohmann::json::input_format_t::json));
    }
    SECTION("bson")
    {
        const auto j = nlohmann::json::parse(str);
        const auto bson = nlohmann::json::to_bson(j);
        Sax</*LexCallImpossible*/ true, T::WithPos, T::WithLex> sax;
        sax.pos_start_object.emplace(4);
        sax.pos_key.emplace(11);
        sax.pos_start_array.emplace(15);
        sax.pos_number_integer.emplace(16);
        sax.pos_number_integer.emplace(23);
        sax.pos_boolean.emplace(30);
        sax.pos_number_float.emplace(34);
        sax.pos_null.emplace(45);
        sax.pos_string.emplace(48);
        sax.pos_end_array.emplace(59);
        sax.pos_end_object.emplace(60);
        CHECK(nlohmann::json::sax_parse(bson, &sax, nlohmann::json::input_format_t::bson));
    }
    SECTION("cbor")
    {
        const auto j = nlohmann::json::parse(str);
        const auto cbor = nlohmann::json::to_cbor(j);
        Sax</*LexCallImpossible*/ true, T::WithPos, T::WithLex> sax;
        sax.pos_start_object.emplace(1);
        sax.pos_key.emplace(7);
        sax.pos_start_array.emplace(8);
        sax.pos_number_unsigned.emplace(13);
        sax.pos_number_integer.emplace(14);
        sax.pos_boolean.emplace(15);
        sax.pos_number_float.emplace(24);
        sax.pos_null.emplace(25);
        sax.pos_string.emplace(29);
        sax.pos_end_array.emplace(29);
        sax.pos_end_object.emplace(29);
        CHECK(nlohmann::json::sax_parse(cbor, &sax, nlohmann::json::input_format_t::cbor));
    }
    SECTION("msgpack")
    {
        const auto j = nlohmann::json::parse(str);
        const auto cbor = nlohmann::json::to_msgpack(j);
        Sax</*LexCallImpossible*/ true, T::WithPos, T::WithLex> sax;
        sax.pos_start_object.emplace(1);
        sax.pos_key.emplace(7);
        sax.pos_start_array.emplace(8);
        sax.pos_number_unsigned.emplace(13);
        sax.pos_number_integer.emplace(14);
        sax.pos_boolean.emplace(15);
        sax.pos_number_float.emplace(24);
        sax.pos_null.emplace(25);
        sax.pos_string.emplace(29);
        sax.pos_end_array.emplace(29);
        sax.pos_end_object.emplace(29);
        CHECK(nlohmann::json::sax_parse(cbor, &sax, nlohmann::json::input_format_t::msgpack));
    }
    SECTION("ubjson")
    {
        const auto j = nlohmann::json::parse(str);
        const auto cbor = nlohmann::json::to_ubjson(j);
        Sax</*LexCallImpossible*/ true, T::WithPos, T::WithLex> sax;
        sax.pos_start_object.emplace(2);
        sax.pos_key.emplace(8);
        sax.pos_start_array.emplace(10);
        sax.pos_number_integer.emplace(14);
        sax.pos_number_integer.emplace(16);
        sax.pos_boolean.emplace(17);
        sax.pos_number_float.emplace(26);
        sax.pos_null.emplace(27);
        sax.pos_string.emplace(33);
        sax.pos_end_array.emplace(34);
        sax.pos_end_object.emplace(35);
        CHECK(nlohmann::json::sax_parse(cbor, &sax, nlohmann::json::input_format_t::ubjson));
    }
}
