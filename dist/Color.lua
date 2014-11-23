function component(name)
	local c = {}	-- New component type
	
	c.name = name	-- Store component type name
	
	return c		-- Return component type
end

local Color = component("Color")

function Color.update(dt)
	print("Updating color")
end

function Color.render()
	print("Rendering color")
end

return Color