-- package.path = '/usr/local/luajit/share/lua/5.1/?.lua;'
-- package.cpath = '/usr/local/luajit/lib/lua/5.1/?.so;'

-- package.path = '/home/jevstein/package/luasocket-2.0.2/src/?.lua;'
-- package.cpath = '/usr/local/lib/lua/5.2/?.so;'

package.cpath = package.cpath .. ";/usr/local/lib/?.so"
require('TSocket')

local socket = require("socket")
 
print(socket.dns.gethostname())
