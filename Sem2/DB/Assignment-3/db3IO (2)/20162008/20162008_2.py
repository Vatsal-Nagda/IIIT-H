from __future__ import division
import sys

class Undo_Recovery:
    def __init__(self):
        self.commited_transactions = []
        self.active_transactions = []
        self.started_transactions = []
        self.transaction_names=[]
        self.logs = []
        self.variables = {}
        self.updated_variable_names=[]


    def processVariables(self,vars):
        vars = vars.split(' ')
        i=0
        while i < len(vars):
            self.variables[vars[i]] = int(vars[i+1])
            # self.variable_names.append(vars[i])
            i+=2

    def process_log(self,log):
        """ Tokenises the logs and returns tokens
        along with the type of the log entry"""
        log_type=""
        if log.lower().endswith('start>'):
            temp = log.strip().split(',')
            log_type='start'
            temp[0] = temp[0][temp[0].find('<')+1:].strip()
            return (log_type,temp)

        if log.lower().endswith('commit>'):
            temp = log.strip().split(',')
            log_type='commit'
            temp[0] = temp[0][temp[0].find('<')+1:].strip()
            return (log_type,temp)

        if log.lower().startswith('<end ckpt>'):
            log_type = 'end ckpt'
            return (log_type,log)

        if log.lower().startswith('<start ckpt'):
            log_type = 'start ckpt'
            temp = log[log.find('<start ckpt')+11: log.find('>')].split(',')
            temp = [x.strip() for x in temp]
            return (log_type,temp)

        temp = log[log.find('<')+1:log.find('>')].split(',')
        temp = [x.strip() for x in temp]
        log_type = 'update'
        return (log_type,temp)

    def reverse_logs_pass1(self):
        pass
        isEndckpt=False
        isStrtckpt = False

        for index,log in enumerate(reversed(self.logs[1:])):
            # print log
            log_type,tokens = self.process_log(log)
            # print log,log_type,tokens


            if log_type == 'start':
                self.started_transactions.append(tokens[0])
                if isStrtckpt == True :
                    if tokens[0] in self.active_transactions :
                        self.active_transactions.remove(tokens[0])
                    if len(self.active_transactions) == 0:
                        # print "All active transactions found"
                        break
            elif log_type == 'commit':
                self.commited_transactions.append(tokens[0])
            elif log_type == 'start ckpt':
                isStrtckpt = True
                self.active_transactions.extend(tokens)
                self.active_transactions = [item for item in self.active_transactions if item not in self.commited_transactions]
                if isEndckpt == True:
                    # print "Break due to End ckpt and start ckpt found both"
                    break
            elif log_type == 'end ckpt':
                isEndckpt = True
        self.active_transactions = [item for item in self.started_transactions if item not in self.commited_transactions]
        # print self.active_transactions
        # print index
        return index

    def reverse_logs_pass2(self,index):
        pass
        for i in xrange(index+1):
            # print self.logs[len(self.logs) - i -1]
            log_type,tokens = self.process_log(self.logs[len(self.logs) - i -1])
            if log_type == 'update':
                # print self.logs[len(self.logs) - i -1]
                transaction = tokens[0]
                var = tokens[1]
                value = int(tokens[2])
                if transaction in self.active_transactions:
                    # print transaction,var,value
                    self.variables[var] = value
                    if var not in self.updated_variable_names:
                        self.updated_variable_names.append(var)

    def read_logs(self,filename):
        f = open(filename,'r')
        for line in f:
            if len(line.strip()) > 0:
                self.logs.append(line.strip())
                # print line.strip()
        self.processVariables(self.logs[0])
        index = self.reverse_logs_pass1()
        self.reverse_logs_pass2(index)

        # print self.updated_variable_names
        self.updated_variable_names.sort()
        for item in self.updated_variable_names:
            sys.stdout.write(item+" "+str(self.variables[item])+" ")
        print ""


if __name__ == '__main__' :
    Undo = Undo_Recovery()
    Undo.read_logs(sys.argv[1])
