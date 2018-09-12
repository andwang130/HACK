import tornado.ioloop
from Handler import *
import tornado.httpserver
import pymongo
import os
import time
from conf import *
from urls import urllist
from tornado.options import define,options
define('port',default=8080,help="run on the given port",type=int)
class appitcaion(tornado.web.Application):
    def __init__(self):
        self.settings=settings
        tornado.web.Application.__init__(self,**self.settings)
if __name__ == '__main__':
    httpserver=tornado.httpserver.HTTPServer(appitcaion())
    httpserver.listen(8080,address='0.0.0.0')
    tornado.ioloop.IOLoop.current().start()#开启服务器