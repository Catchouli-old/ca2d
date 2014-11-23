obj = {}

function obj:test(a, b, c, d, e, f)
	io.write("values: ")
	print(a, b, c, d, e, f)
	return a, b, c, d, e, f
end

function obj:update(dt)
	print("updating: " .. dt)
end

function obj:render()
	print("rendering")
end