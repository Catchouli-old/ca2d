require("engine")

for key,value in pairs(engine) do
    print("found member " .. key);
end

width = 200
height = 300

function f (x, y)
	return x ^ y
end

print("CONFIG")