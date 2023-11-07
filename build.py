
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
    
    @staticmethod
    def constructfromfile(path):
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
    
    def setheader(self, header):
        self.header = header
    
class HeaderFile(CppFile):
    def __init__(self, name, content, path = ""):
        super().__init__(name, content, path)
        self.sources = []
    def __str__(self):
        return super().__str__() + '\n' + str(self.sources)
    def __repr__(self):
        return super().__repr__() + '\n' + str(self.sources)
    
    def addsource(self, source):
        self.sources.append(source)

class CodeSorter:
    def __init__(self, content: CppFile):
        self.headers = []
        self.sources = []
        self.content = content

    def getheaders(self):
        return self.headers

    def moveincludestotop(self):
        file_content = self.content.content
        includes = []
        for line in file_content.split('\n'):
            if line.startswith('#include'):
                #check for duplicate
                if line in includes:
                    continue
                includes.append(line)
                #remove the include from the file
                file_content = file_content.replace(line, '')
        #add the includes to the top of the file
        for include in includes:
            file_content = include + '\n' + file_content
        return includes


    def sortdeclaration(self):
        pass




def main() :
    header_path = "./classes.h"
    source_path = "./subscriberobj.cpp"
    header = HeaderFile.constructfromfile(header_path)
    source = SourceFile.constructfromfile(source_path)
    code_sorter: CodeSorter = CodeSorter(header)
    found_includes = code_sorter.moveincludestotop()


main()