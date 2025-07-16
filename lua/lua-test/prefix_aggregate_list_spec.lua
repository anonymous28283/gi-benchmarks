describe("Prefix Aggregate List", function()
	local pla = require("data_structures.prefix_aggregate_list")
	local function add(a, b)
		return a + b
	end
	local function sub(a, b)
		return a - b
	end
	local function mul(a, b)
		return a * b
	end
	local function div(a, b)
		return a / b
	end
	describe("selected test cases", function()
		local function test(name, op, inv_op)
			it(name, function()
				local vals = { 1, 2, 3 }
				local aggs = pla.new(op, inv_op, vals)
				assert.equal(op(vals[1], vals[2]), aggs:aggregate(1, 2))
				assert.equal(op(vals[2], vals[3]), aggs:aggregate(2, 3))
				local val = 4
				aggs:append(val)
				table.insert(vals, val)
				assert.equal(op(op(vals[2], vals[3]), vals[4]), aggs:aggregate(2, 4))
			end)
		end
		test("sums", add, sub)

		test("products", mul, div)
	end)

	it("random test cases sums", function()

		local random_vals = {}
		local len = math.random(1e3)
		for i = 1, len do
			random_vals[i] = math.random(-1e3, 1e3)
		end

		local sums = pla.new(add, sub, random_vals)
		for _ = 1, len do

			local from = math.random(#random_vals)
			local to = math.random(from, #random_vals)

			local sum = 0
			for i = from, to do
				sum = sum + random_vals[i]
			end

			assert.equal(sum, sums:aggregate(from, to))

			local new_val = math.random(-1e3, 1e3)
			table.insert(random_vals, new_val)
			sums:append(new_val)
		end
	end)
end)
