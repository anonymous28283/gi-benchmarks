describe("Heap", function()
	local shuffle = require("random.shuffle")
	local heap = require("data_structures.heap")
	local function test(aspect, build)
		it(aspect, function()

			local list = {}
			for index = 1, 100 do
				list[index] = index
			end
			shuffle(list)

			local nums = build(list)

			for index = 1, #list do
				assert.equal(#list - index + 1, nums:size())
				assert.equal(index, nums:top())
				local popped = nums:pop()
				assert.equal(index, popped)
			end
			assert(nums:empty())
		end)
	end
	test("building & popping", function(list)


		local copy = {}
		for i, num in ipairs(list) do
			copy[i] = num
		end
		return heap.new(copy)
	end)
	test("inserting & popping", function(list)

		local nums = heap.new()
		assert(nums:empty())
		for i, num in ipairs(list) do
			nums:push(num)
			assert.equal(i, nums:size())
		end
		return nums
	end)
end)
