



local gcd = require("math.greatest_common_divisor")
local intpow = require("math.intpow")

local fraction = {}

local metatable = { __index = fraction }

local function shorten(self)

	local divisor = gcd(self.numerator, self.denominator)
	self.numerator = self.numerator / divisor
	self.denominator = self.denominator / divisor
	if self.denominator < 0 then
		self.denominator = -self.denominator
		self.numerator = -self.numerator
	end
end

local function extend_to_common_denominator(self, other)
	local divisor = gcd(self.denominator, other.denominator)
	local extend_other = self.denominator / divisor
	return other.denominator / divisor * self.numerator,
		extend_other * other.numerator,
		extend_other * other.denominator
end

local function new(numerator, denominator)
	return setmetatable({ numerator = numerator, denominator = denominator }, metatable)
end



fraction.zero = new(0, 1)
fraction.one = new(1, 1)



function fraction.new(numerator, denominator)
	assert(denominator ~= 0)
	local self = new(numerator, denominator)
	shorten(self)
	return self
end

function fraction.from_number(
	number
)
	local denominator = 1
	while number % 1 ~= 0 do
		number = number * 2
		denominator = denominator * 2
	end
	return fraction.new(number, denominator)
end

function fraction.from_string(
	str
)
	local numerator, denominator = str:match("^(.-)/(.+)")
	return fraction.new(assert(tonumber(assert(numerator))), assert(tonumber(denominator)))
end

local function read_base_param(base)
	base = base or 10
	assert(base % 1 == 0 and base >= 2 and base <= 36, "invalid base")
	return base
end

local function parse_positive_double_string(
	str,
	base
)
	base = read_base_param(base)
	local function read_number(str_)
		return assert(tonumber(str_, base))
	end

	local integer, fractional = str:match("^([0-9a-zA-Z][0-9a-zA-Z]-)%.([0-9a-zA-Z%(%)]+)")
	if not fractional then
		assert(str:match("[0-9a-zA-Z]+"))
		return new(read_number(str), 1)
	end

	local pre_period, period = fractional:match("^([0-9a-zA-Z]-)%(([0-9a-zA-Z]+)%)$")
	if not period then
		return read_number(integer) + fraction.new(read_number(fractional), base ^ #fractional)
	end

	local after_dot = (
		read_number(pre_period == "" and "0" or pre_period)
		+ fraction.new(read_number(period), base ^ #period - 1)
	)
	return read_number(integer) + after_dot / base ^ #pre_period
end

function fraction.from_float_string(
	str,
	base
)
	if str:sub(1, 1) == "-" then
		return -parse_positive_double_string(str:sub(2), base)
	end
	return parse_positive_double_string(str, base)
end



function metatable:__tostring()
	return self.numerator .. "/" .. self.denominator
end

local function digit(value)
	if value < 10 then
		return string.char(("0"):byte() + value)
	end

	return string.char(("a"):byte() + value - 10)
end


function fraction:to_float_string(
	base
)
	base = read_base_param(base)
	local base_fraction = new(base, 1)


	local sign = ""
	if self < fraction.zero then
		sign = "-"
		self = -self
	end


	local fractional = self % fraction.one
	local integer = self - fractional
	assert(integer.denominator == 1)
	integer = integer.numerator


	local int_digits = {}
	while integer ~= 0 do
		local digit_value = integer % base
		table.insert(int_digits, digit(digit_value))
		integer = (integer - digit_value) / base
	end

	int_digits = table.concat(int_digits):reverse()
	if int_digits == "" then
		int_digits = 0
	end

	if fractional == fraction.zero then
		return sign .. int_digits
	end

	local seen_divisions = {}
	local fractional_digits = {}
	while fractional ~= fraction.zero do

		local div_key = ("%x/%x"):format(fractional.numerator, fractional.denominator)
		local last_digit_index = seen_divisions[div_key]
		if last_digit_index then
			local pre_period_digits = last_digit_index > 1
					and table.concat(fractional_digits, "", 1, last_digit_index - 1)
				or ""
			local period = "(" .. table.concat(fractional_digits, "", last_digit_index) .. ")"

			return sign .. int_digits .. "." .. pre_period_digits .. period
		end

		local digit_index = #fractional_digits + 1
		seen_divisions[div_key] = digit_index

		fractional = fractional * base_fraction
		local remaining_fractional = fractional % fraction.one
		local digit_value = fractional - remaining_fractional
		assert(digit_value.denominator == 1)
		digit_value = digit_value.numerator
		fractional_digits[digit_index] = digit(digit_value)
		fractional = remaining_fractional
	end

	fractional_digits = table.concat(fractional_digits)

	return sign .. int_digits .. "." .. fractional_digits
end

function fraction:to_number()
	return self.numerator / self.denominator
end



local function bin_op(name, operator)
	metatable["__" .. name] = function(self, other)

		if type(self) == "number" then
			self = fraction.from_number(self)
		elseif type(other) == "number" then
			other = fraction.from_number(other)
		end
		return operator(self, other)
	end
end



metatable.__pow = intpow

bin_op("add", function(self, other)
	local self_numerator, other_numerator, common_denominator = extend_to_common_denominator(self, other)
	return fraction.new(self_numerator + other_numerator, common_denominator)
end)

bin_op("sub", function(self, other)
	local self_numerator, other_numerator, common_denominator = extend_to_common_denominator(self, other)
	return fraction.new(self_numerator - other_numerator, common_denominator)
end)

bin_op("mul", function(self, other)
	return fraction.new(self.numerator * other.numerator, self.denominator * other.denominator)
end)

bin_op("div", function(self, other)
	assert(other.numerator ~= 0, "division by zero")
	return fraction.new(self.numerator * other.denominator, self.denominator * other.numerator)
end)

bin_op("mod", function(self, other)
	local self_numerator, other_numerator, common_denominator = extend_to_common_denominator(self, other)
	return fraction.new(self_numerator % other_numerator, common_denominator)
end)



function metatable:__unm()
	return new(-self.numerator, self.denominator)
end



bin_op("eq", function(self, other)

	return self.numerator == other.numerator and self.denominator == other.denominator
end)

bin_op("lt", function(self, other)
	local self_numerator, other_numerator = extend_to_common_denominator(self, other)
	return self_numerator < other_numerator
end)


bin_op("le", function(self, other)
	local self_numerator, other_numerator = extend_to_common_denominator(self, other)
	return self_numerator <= other_numerator
end)

return fraction
