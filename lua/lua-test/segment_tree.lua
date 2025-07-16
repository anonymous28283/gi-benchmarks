



local segment_tree = {}


function segment_tree.new(

	binary_op,

	vals
)
	vals = vals or {}
	local nodes = {}
	local function build(idx, from, to)
		if from == to then



			nodes[idx] = vals[from]
			return
		end
		local left_idx, right_idx = 2 * idx, 2 * idx + 1
		local mid = math.floor((from + to) / 2)
		build(left_idx, from, mid)
		build(right_idx, mid + 1, to)
		nodes[idx] = binary_op(nodes[left_idx], nodes[right_idx])
	end
	if #vals > 0 then
		build(1, 1, #vals)
	end

	return {
		op = binary_op,
		len = #vals,
		nodes = nodes,
	}
end


function segment_tree:update(
	idx,
	val
)
	local op, nodes = self.op, self.nodes
	local function set(seg_idx, seg_from, seg_to)
		if seg_from == seg_to then
			assert(idx == seg_from, "out of bounds")
			nodes[seg_idx] = val
			return
		end

		local seg_mid = math.floor((seg_from + seg_to) / 2)
		local left_idx, right_idx = 2 * seg_idx, 2 * seg_idx + 1
		if idx <= seg_mid then
			set(left_idx, seg_from, seg_mid)
		else
			set(right_idx, seg_mid + 1, seg_to)
		end

		nodes[seg_idx] = op(nodes[left_idx], nodes[right_idx])
	end
	set(1, 1, self.len)
end

function segment_tree:aggregate(

	from,

	to
)
	from, to = from or 1, to or self.len
	local op, nodes = self.op, self.nodes
	local function get(seg_idx, seg_from, seg_to, want_from, want_to)
		if want_from == seg_from and want_to == seg_to then
			return nodes[seg_idx]
		end

		local seg_mid = math.floor((seg_from + seg_to) / 2)
		local left_idx, right_idx = 2 * seg_idx, 2 * seg_idx + 1
		if want_to <= seg_mid then
			return get(left_idx, seg_from, seg_mid, want_from, want_to)
		end
		if want_from >= seg_mid + 1 then
			return get(right_idx, seg_mid + 1, seg_to, want_from, want_to)
		end




		return op(
			get(left_idx, seg_from, seg_mid, want_from, seg_mid),
			get(right_idx, seg_mid + 1, seg_to, seg_mid + 1, want_to)
		)
	end
	return get(1, 1, self.len, from, to)
end

return require("class")(segment_tree)
