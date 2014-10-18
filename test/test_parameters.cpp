/*
 * Copyright (C) MediaSift Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <served/parameters.hpp>

TEST_CASE("Test param const, ref and copy handling", "[parameters]")
{
	served::parameters params;
	params["value1"] = "value one";
	params.set("value2", "value two");

	auto test_copy = [](served::parameters p)
	{
		REQUIRE ( p["value1"] == "value one" );
		REQUIRE ( p["value2"] == "value two" );
		REQUIRE ( p["value3"] == "" );

		REQUIRE ( p.get("value1") == "value one" );
		REQUIRE ( p.get("value2") == "value two" );
		REQUIRE ( p.get("value3") == "" );

		p["value1"] = "new value one";
		p["value2"] = "new value two";
		p["value3"] = "new value three";

		REQUIRE ( p["value1"] == "new value one" );
		REQUIRE ( p["value2"] == "new value two" );
		REQUIRE ( p["value3"] == "new value three" );
	};

	auto test_const_copy = [](const served::parameters p)
	{
		REQUIRE ( p["value1"] == "value one" );
		REQUIRE ( p["value2"] == "value two" );
		REQUIRE ( p["value3"] == "" );

		REQUIRE ( p.get("value1") == "value one" );
		REQUIRE ( p.get("value2") == "value two" );
		REQUIRE ( p.get("value3") == "" );
	};

	auto test_const_ref = [](served::parameters const& p)
	{
		REQUIRE ( p["value1"] == "value one" );
		REQUIRE ( p["value2"] == "value two" );
		REQUIRE ( p["value3"] == "" );

		REQUIRE ( p.get("value1") == "value one" );
		REQUIRE ( p.get("value2") == "value two" );
		REQUIRE ( p.get("value3") == "" );
	};

	test_copy      (params);
	test_const_copy(params);
	test_const_ref (params);
}
