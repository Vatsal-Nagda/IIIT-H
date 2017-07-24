from __future__ import division
import csv
import sys

class Logging_Recovery():
    def __init__(self,quant):
        self.variables = {}
        self.variable_names=[]
        self.variables_temporary=[]
        self.quantum = quant
        self.transactions=[]
        self.transaction_names=[]
        self.transaction_ptrs = []

    def print_variables(self):
        for i in xrange(len(self.variable_names)):
            sys.stdout.write(self.variable_names[i]+" "+str(self.variables[self.variable_names[i]])+" ")
        print

    def processVariables(self,vars):
        vars = vars.split(' ')
        i=0
        while i < len(vars):
            self.variables[vars[i]] = int(vars[i+1])
            self.variable_names.append(vars[i])
            i+=2
        # print self.variables

    def calculate_value(self,rhs,opr,i):
        var1 = rhs.split(opr)[0].strip()
        var2 = rhs.split(opr)[1].strip()
        var1 = self.variables_temporary[i][var1]
        if var2.isdigit() == True:
            var2 = int(var2)
        else:
            var2 = self.variables_temporary[i][var2]

        if opr == '+':
            return var1 + var2
        elif opr == '-':
            return var1 - var2
        elif opr == '*':
            return var1 * var2
        elif opr == '/':
            return var1 / var2


    def report_log(self,i,var_to_write):
        print "<"+self.transaction_names[i]+", "+var_to_write+", "+str(self.variables[var_to_write])+">"

    def processQuery(self,query,i):
        oprtr = ['+','-','*','/']
        """ i is transaction number , rr_iter is the round robin iteration number
         here we will process various types of logs """
        # print i,query
        if query.startswith('read'):
            instruction = query[query.find("(")+1:query.find(")")]
            # print instruction
            var_from_read = instruction.split(",")[0]
            var_to_read = instruction.split(",")[1]
            self.variables_temporary[i][var_to_read] = self.variables[var_from_read]
            # print self.variables_temporary[i][var_to_read],self.variables[var_from_read]
        elif query.startswith('write'):
            # print "<T"+str(i+1)+" ,start>"
            instruction = query[query.find("(")+1:query.find(")")]
            # print instruction
            var_to_write = instruction.split(",")[0]
            var_from_write = instruction.split(",")[1]
            self.report_log(i,var_to_write)
            self.variables[var_to_write] = self.variables_temporary[i][var_from_write]
            self.print_variables()
        elif query.startswith('output'):
            # pass
            if self.transaction_ptrs[i] < len(self.transactions[i])-1 :
                pass
            else:
                print "<"+self.transaction_names[i]+", commit>"
                self.print_variables()


        else:
            lhs = query.split('=')[0]
            rhs = query.split('=')[1].strip()
            if lhs[-1] == ':':
                lhs = lhs[:-1]
            lhs = lhs.strip()

            for opr in oprtr:
                if opr in rhs:
                    break

            rhs = self.calculate_value(rhs,opr,i)
            # print lhs," to be assigned ",rhs
            self.variables_temporary[i][lhs] = rhs
            # self.print_variables()


    def separateTransactions(self,transactions):
        temp=[]

        iteration_num = 0
        for i in xrange(len(transactions)):
            # print i,transactions[i],iteration_num
            if 0 == iteration_num :
                x = transactions[i].split(" ")
                """ Identify the name and no of lines in a transaction """
                # print x
                transaction_name = x[0]
                num_transactions = int(x[1])
                # print transaction_name,num_transactions,iteration_num
                self.transaction_names.append(transaction_name)
                self.variables_temporary.append({})
                iteration_num += 1
                # print iteration_num
            elif num_transactions == iteration_num:
                temp.append(transactions[i])
                self.transactions.append(temp)
                iteration_num = 0
                temp=[]
            else:
                temp.append(transactions[i])
                # print iteration_num,transactions[i]
                iteration_num += 1

        # print self.transactions

    def roundRobin(self):
        """ Simulating the round robin fashion of interleaving """
        self.transaction_ptrs = [0]*len(self.transactions)
        """ starting pointer for every transaction in the input """
        i=0;
        flag = True
        rr_iter=0
        while True:
            if rr_iter == 0:
                print "<"+self.transaction_names[i]+", start>"
                self.print_variables()

            # print self.transaction_names[i]
            for j in xrange(self.quantum):
                if self.transaction_ptrs[i] < len(self.transactions[i]):
                    # print transaction_ptrs[i],len(self.transactions[i])
                    # print self.transactions[i][transaction_ptrs[i]]
                    self.processQuery(self.transactions[i][self.transaction_ptrs[i]],i)
                    self.transaction_ptrs[i] += 1
            # print "=================NEXT ROUND============="

            i = (i+1)% len(self.transaction_names)
            flag = True
            if i ==0:
                rr_iter += 1
                for j in xrange(len(self.transaction_ptrs)):
                    if self.transaction_ptrs[j] < len(self.transactions[j]):
                        flag = False
                        break

                if flag == True:
                    break

    def read_transactions(self,filename):
        f= open(filename,'r')
        transactions = []
        for line in f:
            if len(line.strip())!= 0 :
                transactions.append(line.strip())
        # print temp
        self.processVariables(transactions[0])
        # print transactions[1:]
        self.separateTransactions(transactions[1:])


if __name__ == '__main__':
    Log = Logging_Recovery(int(sys.argv[2]))
    Log.read_transactions(sys.argv[1])
    Log.roundRobin()
