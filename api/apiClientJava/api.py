
callback = None

def registerCallback(k):
    global callback
    callback = k

def getCallback():
    return callback



