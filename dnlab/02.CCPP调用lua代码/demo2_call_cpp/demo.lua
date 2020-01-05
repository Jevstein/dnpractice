
package.cpath = package.cpath .. ";./lcpp/?.so"

require("libmyluamath")

local a = 200
local b = 100

local ret = MyMath.add(a, b)
print("a + b = " ..a .. " + " .. b .. " = "..ret)

local ret = MyMath.sub(a, b)
print("a - b = " ..a .. " - " .. b .. " = "..ret)

local ret = MyMath.mul(a, b)
print("a * b = " ..a .. " * " .. b .. " = "..ret)

local ret = MyMath.div(a, b)
print("a / b = " ..a .. " / " .. b .. " = "..ret)