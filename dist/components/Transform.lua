local Transform = {}
Transform.__index = Transform

-- Allow Transform() constructor calls
setmetatable(Transform,
{
	__call = function(cls, ...)
		return cls.new(...)
	end,
})

-- Constructor
function Transform.new(x, y)
	local self = setmetatable({}, Transform)
	
	self.x = x or 0
	self.y = y or 0
	
	return self
end

-- Update
function Transform:update()
	print("Updating component")
end

-- Render
function Transform:render()
	print("Rendering component")
end

return Transform