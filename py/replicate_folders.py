import sys
import os
import shutil
import openpyxl

################### To be edited by user #########################################################################################
#define list of lives and batches you want to make a directory for
G_CYCLES = [1, 3, 7]
G_BATCHES = []
####################################################################################################################################

#Global constants
G_CYCLE_CELL = 'C7'                          #cell that holds cycle number to be edited
G_CWD = os.getcwd()                         #save script's directory
G_XLSOURCE = os.path.join(G_CWD, "source")  #source directory for datasheets

G_DELIMITER = " - "
G_CYCLE_TOKEN = "L"
G_BATCH_TOKEN = "Batch"


#make list of excel files to be copied
G_XL_LIST = []
for file in os.listdir(G_XLSOURCE):
    if file.endswith(".xlsx"):
        G_XL_LIST.append(os.path.join(G_XLSOURCE, file))

def parseArgs():
    args = sys.argv[1].split()
    listints = []
    for arg in args:
        intarg = int(arg)
        listints.append(intarg)

    print(listints)
    return listints    
    

#edit a single cell of a single excel file
def editDatasheet(file, cell, cellval):
        
    workbook = openpyxl.load_workbook(filename = file)
    worksheet = workbook.active
    worksheet[cell] = cellval

    workbook.save(file)

def main():
    cycles = parseArgs()
    if not cycles:
        cycles = G_CYCLES

    for cycle in cycles:
        cycledir = os.path.join(G_CWD, G_CYCLE_TOKEN + "=" + str(cycle))

        #if there are batches with testing (list not empty), make batch subdirectories and datasheets
        if G_BATCHES:
            for batch in G_BATCHES:
                batchdir = os.path.join(G_CWD, cycledir, G_BATCH_TOKEN + str(batch))
                os.makedirs(batchdir, exist_ok = True)
                for xlfile in G_XL_LIST:
                    print(xlfile)
                    filename = os.path.splitext(os.path.basename(xlfile))[0] + G_DELIMITER + G_CYCLE_TOKEN + str(cycle) + G_DELIMITER + G_BATCH_TOKEN + str(batch) + ".xlsx"
                    datasheetpath = os.path.join(batchdir, filename)
                    print("Creating: " + datasheetpath)

                    shutil.copy2(xlfile, datasheetpath)  
                    editDatasheet(datasheetpath, G_CYCLE_CELL, cycle)

        #if there are no batches with testing (list empty), make cycle directory and datasheets
        else:
            os.makedirs(cycledir, exist_ok = True)
            for xlfile in G_XL_LIST:
                filename = os.path.splitext(os.path.basename(xlfile))[0] + G_DELIMITER + G_CYCLE_TOKEN + str(cycle)
                print(filename)
                datasheetpath = os.path.join(cycledir, filename + ".xlsx")
                print("Creating: " + datasheetpath)

                shutil.copy2(xlfile, datasheetpath)
                editDatasheet(datasheetpath, G_CYCLE_CELL, cycle)

if __name__ == "__main__":
    main()