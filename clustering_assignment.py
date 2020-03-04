import pandas as pd
import copy as cp
import matplotlib.pyplot as plt


def normalize(df):
    temp_n_df = cp.deepcopy(df);
    for col_name in df:
        max_v = max(df[col_name])
        min_v = min(df[col_name])
        temp_n_df[col_name] = (temp_n_df[col_name] - min_v)/(max_v - min_v)        
    return temp_n_df  


def find_diff(df,j,i):
    diff = df.loc[j] - df.loc[i]
    num = 0
    for k in diff.values:
        num = num + k ** 2
    num = num ** 0.5
    return num    

    
def dissimilarity(df):
    dis_df = pd.DataFrame(0.0,index = range(len(df)),columns = range(len(df)))
    for i in range(0,len(df)):
        for j in range(0,len(df)):
            #print(find_diff(df,j,i))
            dis_df[j][i] = find_diff(df,j,i)
    return dis_df
                    

def form_clusters(diff_df):
    avg_diss = diff_df.mean()
    cluster_matrix = [[]] * len(diff_df)
    for i in range(0,len(diff_df)):
        local = []
        for j in range(0,len(diff_df)):
            if(diff_df[j][i] < avg_diss[i]):
                local.append(j)
        cluster_matrix[i] = local
    return cluster_matrix


def rm_clusters_overlap(clusters_matrix):
    cm = cp.deepcopy(clusters_matrix)
    
    for i in range(0,len(cm)):
        for j in range(0,len(cm)):
            if(i != j):
                if(set(cm[j]).issubset(set(cm[i]))):
                    cm[j] = []
    
    fin_c = []
    
    for i in range(0,len(cm)):
        if(cm[i] != []):
            fin_c.append(cm[i])  

    return fin_c

def find_sim(cl,j,i):
    intr = len(set(cl[j]).intersection(set(cl[i])))
    unon = len(set(cl[i]).union(set(cl[j])))
    num = intr/unon
    return num

def simm_cluster(cluster):
    simmc = pd.DataFrame(0.0,index = range(len(cluster)),columns = range(len(cluster)))
    for i in range(0,len(cluster)):
        for j in range(0,len(cluster)):
            #print(find_diff(df,j,i))
            simmc[j][i] = find_sim(cluster,j,i)
    return simmc

def merged_cl(simcl,fcl):
    simcl_w1 = cp.deepcopy(simcl)
    for i in range(0,len(simcl)):
        simcl_w1[i][i] = 0
    
    maxn = simcl_w1.values.max()
    c = 0
    r = 0
    
    for i in range(0,len(simcl)):
        for j in range(0,len(simcl)):
            if(simcl_w1[j][i] == maxn):
                c = j
                r = i
                break

    fcl[c] = list(set(fcl[c]).union(set(fcl[r])))
    del fcl[r]
    return fcl

def findcent(l,normdf):
    z = [0] * 4
    for i in range(0,len(l)):
        z = z + normdf.loc[l[i]]
    z = z/len(l)
    return z

def find_dist(normdf,i,cent):
    x = normdf.loc[i]
    dist = ((x[0] - cent[0]) ** 2 + (x[1] - cent[1]) ** 2 + (x[2] - cent[2]) ** 2 + (x[3] - cent[3]) ** 2) ** 0.5
    return dist

def final_clusterize(simcl,fcl,normdf):
    
    centone = findcent(fcl[0],normdf)
    centtwo = findcent(fcl[1],normdf)
    centthree = findcent(fcl[2],normdf)
    final = [[]]*3
    la = []
    lb = []
    lc = []
    for i in range(0,len(normdf)):
        a = int(i in fcl[0])
        b = int(i in fcl[1])
        c = int(i in fcl[2])
        a_dist = a * find_dist(normdf,i,centone)
        b_dist = b * find_dist(normdf,i,centtwo)
        c_dist = c * find_dist(normdf,i,centthree)
        
        z = []
        z.append(a_dist)
        z.append(b_dist)
        z.append(c_dist)
        for j in range(0,2):
            if(z[j] == 0):
                z.remove(0)
        minv = min(z)
        if(minv == a_dist):
            la.append(i)

        elif(minv == b_dist):
            lb.append(i)
        elif(minv == c_dist):
            lc.append(i)
    final[0] = la
    final[1]=lb
    final[2]=lc
    return final
     

    
#MAIN DRIVER
  
df = pd.read_csv("iris.csv")
del df['fl']
n = - 1
while(n != 0):
    print("///")
    print(" 0 - exit / 1 - Normalize / 2 - Dissimilarity / 3 - Form Clusters / 4 - Remove Subsets / 5 - Similarity for Clusters / 6 - Cluster Merge / 7 - Repeating until Getting 3 Clusters / 8 - FINAL /")
    n = int(input())
    if(n == 1):
        #normalize
        norm_df = normalize(df)
        print(norm_df)
    if(n == 2):
        #dissimilarity
        diss_df= dissimilarity(norm_df)
         
    if(n == 3):
        #form_clusters
        clusters_matrix = form_clusters(diss_df)
    if(n == 4):
        #remove_subset
        f_cluster = rm_clusters_overlap(clusters_matrix)
    if(n == 5):
        #similarity_matrix_for_clusters
        sim_matrix_cluster = simm_cluster(f_cluster)
    if(n == 6):
        #max_val & cluster_merge
        f_cluster = merged_cl(sim_matrix_cluster,f_cluster)
    if(n == 7):
        #loop for k times
        i = 1
        while(i == 1):
            f_cluster = rm_clusters_overlap(f_cluster)
            sim_matrix_cluster = simm_cluster(f_cluster)
            f_cluster = merged_cl(sim_matrix_cluster,f_cluster)
            if(len(f_cluster) == 3):
                break
    if(n == 8):
        #putting_into_single_cluster
        f_cluster = final_clusterize(sim_matrix_cluster,f_cluster,norm_df)
        print("Done")     
    if(n == 0):
        print("exiting")
    else:
        print("Enter a valid argumnet")
        
        
    


