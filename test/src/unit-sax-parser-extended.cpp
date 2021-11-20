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
template <
    bool LexCallImpossible,
    bool WithPos,
    bool WithLex,
    std::size_t NullPos,
    std::size_t BoolPos,
    std::size_t IntPos,
    std::size_t UintPos,
    std::size_t FltPos,
    std::size_t StrPos,
    std::size_t BinPos,
    std::size_t KeyPos,
    std::size_t SObjPos,
    std::size_t EObjPos,
    std::size_t SArrPos,
    std::size_t EArrPos
    >
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
        CHECK(NullPos == pos);
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type null(const LexT& lex)
    {
        CHECK(NullPos == lex.get_position().chars_read_total);
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
        CHECK(BoolPos == pos);
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type boolean(bool /*unused*/, const LexT& lex)
    {
        CHECK(BoolPos == lex.get_position().chars_read_total);
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
        CHECK(IntPos == pos);
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type number_integer(json::number_integer_t /*unused*/, const LexT& lex)
    {
        CHECK(IntPos == lex.get_position().chars_read_total);
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
        CHECK(UintPos == pos);
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type number_unsigned(json::number_unsigned_t /*unused*/, const LexT& lex)
    {
        CHECK(UintPos == lex.get_position().chars_read_total);
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
        CHECK(FltPos == pos);
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type number_float(json::number_float_t /*unused*/, const std::string& /*unused*/, const LexT& lex)
    {
        CHECK(FltPos == lex.get_position().chars_read_total);
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
        CHECK(StrPos == pos);
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type string(std::string& /*unused*/, const LexT& lex)
    {
        CHECK(StrPos == lex.get_position().chars_read_total);
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
        CHECK(BinPos == pos);
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type binary(std::vector<std::uint8_t>& /*unused*/, const LexT& lex)
    {
        CHECK(BinPos == lex.get_position().chars_read_total);
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
        CHECK(SObjPos == pos);
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type start_object(std::size_t /*unused*/, const LexT& lex)
    {
        CHECK(SObjPos == lex.get_position().chars_read_total);
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
        CHECK(KeyPos == pos);
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type key(std::string& /*unused*/, const LexT& lex)
    {
        CHECK(KeyPos == lex.get_position().chars_read_total);
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
        CHECK(EObjPos == pos);
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type end_object(const LexT& lex)
    {
        CHECK(EObjPos == lex.get_position().chars_read_total);
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
        CHECK(SArrPos == pos);
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type start_array(std::size_t /*unused*/, const LexT& lex)
    {
        CHECK(SArrPos == lex.get_position().chars_read_total);
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
        CHECK(EArrPos == pos);
        return true;
    }
    template<class LexT, bool Act = WithLex && !std::is_same<LexT, std::size_t>::value>
    typename std::enable_if<Act, bool>::type end_array(const LexT& lex)
    {
        CHECK(EArrPos == lex.get_position().chars_read_total);
        return true;
    }

    bool parse_error(std::size_t /*unused*/, const std::string& /*unused*/, const json::exception& /*unused*/) // NOLINT(readability-convert-member-functions-to-static)
    {
        return false;
    }
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
    const std::string str = R"({"array" : [1,-1,true,4.2,null,"str"]})";
    SECTION("json")
    {
        Sax <
        /*LexCallImpossible*/ false,
        /*WithPos*/ T::WithPos,
        /*WithLex*/ T::WithLex,
        /*NullPos*/ 30,
        /*BoolPos*/ 21,
        /*IntPos*/ 16,
        /*UintPos*/ 13,
        /*FltPos*/ 25,
        /*StrPos*/ 36,
        /*BinPos*/ 0,
        /*KeyPos*/ 8,
        /*SObjPos*/ 1,
        /*EObjPos*/ 38,
        /*SArrPos*/ 12,
        /*EArrPos*/ 37
        > sax;
        CHECK(nlohmann::json::sax_parse(str, &sax));
    }
    SECTION("bson")
    {
        const auto j = nlohmann::json::parse(str);
        const auto bson = nlohmann::json::to_bson(j);
        Sax<
        /*LexCallImpossible*/ true,
        /*WithPos*/ T::WithPos,
        /*WithLex*/ T::WithLex,
        /*NullPos*/ 45,
        /*BoolPos*/ 30,
        /*IntPos*/ 16,
        /*UintPos*/ 11,
        /*FltPos*/ 34,
        /*StrPos*/ 48,
        /*BinPos*/ 0,
        /*KeyPos*/ 11,
        /*SObjPos*/ 4,
        /*EObjPos*/ 60,
        /*SArrPos*/ 15,
        /*EArrPos*/ 59
        > sax;
        const bool result = nlohmann::json::sax_parse(bson, &sax, nlohmann::json::input_format_t::bson);
        CHECK(result);
    }
}
