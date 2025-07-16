
local function random_bytes(n)
	if n == 0 then
		return
	end
	return math.random(0, 0xFF), random_bytes(n - 1)
end

describe("Levenshtein distance", function()
	local levenshtein_distance = require("string.distance.levenshtein")
	local function test(expected_distance, s, t)
		assert.equal(expected_distance, levenshtein_distance(s, t))
		if s ~= t then
			assert.equal(expected_distance, levenshtein_distance(t, s))

			assert.equal(expected_distance, levenshtein_distance(t:reverse(), s:reverse()))
		end
	end
	it("empty words", function()
		test(0, "", "")
		for i = 1, 10 do
			test(i, ("x"):rep(i), "")
		end
	end)
	it("random strings & substrings", function()
		for _ = 1, 1e3 do

			local random_str = string.char(random_bytes(math.random(5, 25)))

			test(0, random_str, random_str)


			local from = math.random(1, #random_str)
			local to = math.random(from, #random_str)
			local substr = random_str:sub(from, to)


			test(#random_str - #substr, substr, random_str)
		end
	end)
	it("selected strings", function()
		test(1, "fiddle", "riddle")
		test(2, "banana", "ananas")
		test(4, "hello", "world")
	end)
end)
