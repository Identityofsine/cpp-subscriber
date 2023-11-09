import getopt, sys
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

    #cast into Header
    def asheader(self):
        return HeaderFile(self.name, self.content, self.path)

    #cast into Source
    def assource(self):
        return SourceFile(self.name, self.content, self.path)

    def export(self, path = ''):
        # if path is not specified, export to the same path as the original file
        if path == '':
            path = self.path
        try:
            with open(path, 'w') as file:
                file.write(self.content)
        except[IOError, OSError]:
            print("Error: could not export file")


    
    @staticmethod
    #generic
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

    def addline(self, line):
        self.content += line

    def combinesources(self):
        combined = HeaderFile(self.name, self.content, self.path)
        for source in self.sources:
            combined.addline(source.content)
        CodeSorter(combined).moveincludestotop()
        return combined


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
                #check if line includes the CppFile name
                if self.content.name in line:
                    #remove line
                    file_content = file_content.replace(line, '')
                    continue
                #check for duplicates
                if line in includes:
                    continue
                includes.append(line)
                #remove the include from the file
                file_content = file_content.replace(line, '')
#       add the includes to the top of the file
        for include in includes:
            file_content = include + '\n' + file_content
        self.content.content = file_content
        return includes


    def sortdeclaration(self):
       pass



options = "hf:o:"
long_options = ["help", "files", "output"]

def argshandler(args : ['']):
    pass

def help():
    print(f"{__file__} SYNTAX : --files path1 path2 path3 --output path")

def main() :
    # take args in from user --files [...] and --output
    header_path = "./classes.h"
    source_path = "./subscriberobj.cpp"
    header = HeaderFile.constructfromfile(header_path).asheader()
    source = SourceFile.constructfromfile(source_path).assource()
    header.addsource(source)
    combined = header.combinesources()
    combined.export('./includes/fofxsubscriber.h')

main()