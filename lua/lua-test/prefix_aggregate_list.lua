





local pal = {}

function pal.new(

	op,

	inv_op,

	vals
)
	vals = vals or {}
	local aggregates = { vals[1] }
	for i = 2, #vals do
		assert(vals[i] ~= nil)
		aggregates[i] = op(aggregates[i - 1], vals[i])
	end
	return { aggregates = aggregates, op = op, inv_op = inv_op }
end


function pal:append(
	val
)
	assert(val ~= nil)
	local aggregates = self.aggregates
	aggregates[#aggregates + 1] = self.op(aggregates[#aggregates], val)
end


function pal:remove()
	local aggregates = self.aggregates
	aggregates[#aggregates] = nil
end


function pal:aggregate(

	from,

	to
)
	local aggregates = self.aggregates
	from, to = from or 1, to or #aggregates
	if from == 1 then
		return aggregates[to]
	end

	return self.inv_op(aggregates[to], aggregates[from - 1])
end

return require("class")(pal)
