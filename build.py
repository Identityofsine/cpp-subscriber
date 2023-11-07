
# DEFINE a class that will be used to contain a cpp file's content and will be extended to header and source files
class CppFile:
    def __init__(self, name, content, path = ""):
        self.name = name
        self.path = path
        self.content = content
    def __str__(self):
        return self.name + '\n' + self.content
    def __repr__(self):
        return self.name + '\n' + self.content
    
    @static
    def constructFromFile(self, path):
        with open(path, 'r') as file:
            filename = path.split('/')[-1]
            return CppFile(filename, file.read())
     
   
class SourceFile(CppFile):
    def __init__(self, name, content, path = ""):
        super().__init__(name, content, path)
        self.header = None
    def __str__(self):
        return super().__str__() + '\n' + self.header.name
    def __repr__(self):
        return super().__repr__() + '\n' + self.header.name
    
    def setHeader(self, header):
        self.header = header
    
class HeaderFile(CppFile):
    def __init__(self, name, content, path = ""):
        super().__init__(name, content, path)
        self.sources = []
    def __str__(self):
        return super().__str__() + '\n' + str(self.sources)
    def __repr__(self):
        return super().__repr__() + '\n' + str(self.sources)
    
    def addSource(self, source):
        self.sources.append(source)

class CodeSorter:
    def __init__(self, content = ""):
        self.headers = []
        self.sources = []
        self.content = content

    def getHeaders(self):
        return self.headers

    def findHeadersAtTop(self):
        #find the headers at the top
        for line in self.content.splitlines():
            if line.startswith('#'):
                if line.startswith('#include'):
                    self.headers.append(line)
                else:
                    break
            else:
                break
        pass

    def moveIncludesToTop(self):
        #search for includes in content, line by line
        #if found remove, and move to top of content

    def sortDeclaration(self):
        pass






