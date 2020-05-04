#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
import pandas as pd

# Euclidean Distance
def EUC(a):
    a = np.array(pd.DataFrame(a).fillna(False))
    NumUsers = np.size(a, axis = 0)
    Sim = np.full((NumUsers, NumUsers), 0.0)
    for u in range(0, NumUsers):
        for v in range(u, NumUsers):
            tmp = np.sum(np.square(a[u, ] - a[v, ]))
            Sim[u,v] = np.sqrt(tmp)
            Sim[v,u] = Sim[u,v]
    return Sim

# Cosine similarity
def COS(a):
    a = np.array(pd.DataFrame(a).fillna(0))
    NumUsers = np.size(a, axis = 0)
    Sim = np.full((NumUsers, NumUsers), 0.0)
    print("COS calculation start!")
    for u in range(0, NumUsers):
        arridx_u = np.where(a[u, ] == 0)
        for v in range(u, NumUsers):
            arridx_v = np.where(a[v, ] == 0)
            arridx = np.unique(np.concatenate((arridx_u, arridx_v), axis = None))
            
            U = np.delete(a[u, ], arridx)
            V = np.delete(a[v, ], arridx)
            
            u_sum = np.linalg.norm(U)
            v_sum = np.linalg.norm(V)
            uv_dot = np.dot(a[u], a[v])
            
            if(u_sum == 0 or v_sum == 0):
                Sim[u,v] = 0
            else:
                Sim[u,v] = uv_dot / (u_sum * v_sum)
            Sim[v,u] = Sim[u,v]
    
    print("COS calculation end!")
    return Sim

# Pearson Correlation Coefficient
def PCC(mat):
    mat = np.array(pd.DataFrame(mat).fillna(0))
    NumUsers = np.size(mat, axis = 0)
    Sim = np.full((NumUsers, NumUsers), -1.0)
    #배열 a의 크기에 맞게 빈 배열을 만듭니다.
    mean = np.nanmean(np.where(mat!=0, mat, np.nan), axis=1)
    print("PCC calculation start!")
    for u in range(0, NumUsers):
        for v in range(u+1, NumUsers):
            arridx_u = np.where(mat[u, ] == 0)
            arridx_v = np.where(mat[v, ] == 0)
            arridx = np.unique(np.concatenate((arridx_u, arridx_v), axis = None))
      
            U = np.delete(mat[u, ], arridx) - mean[u]
            V = np.delete(mat[v, ], arridx) - mean[v]
            
            if(np.linalg.norm(U) == 0 or np.linalg.norm(V) == 0 ):
                Sim[u, v] = 0
            else:
                Sim[u, v] = np.dot(U, V) / (np.linalg.norm(U) * np.linalg.norm(V))

            Sim[v, u] = Sim[u, v]
    print("PCC calculation end!")
    return Sim


def basic_CF(mat, sim, k):
    predicted_rating = np.array([[0.0 for col in range(mat.shape[1])] for row in range(mat.shape[0])])
    
    if(sim == 'COS'):
        Sim = COS(mat)
    else:
        Sim = PCC(mat)
    
    
    k_neighbors = np.argsort(-Sim)
    k_neighbors = np.delete(k_neighbors, np.s_[k:],1)
    
    mat = np.array(pd.DataFrame(mat).fillna(0))
    NumUsers = np.size(mat, axis = 0)
    
    for u in range(0, NumUsers):
        list_sim = Sim[u, k_neighbors[u,]]
        list_rating = mat[k_neighbors[u],].astype('float64')
        
        if np.sum(list_sim) == 0 :
            predicted_rating[u, ] = 0
        else:
            predicted_rating[u, ] = np.sum(list_sim.reshape(-1, 1) * list_rating, axis = 0) / np.sum(list_sim)
        
    return predicted_rating



def basic_mean(mat, sim, k):
    predicted_rating = np.array([[0.0 for col in range(mat.shape[1])] for row in range(mat.shape[0])])
    
    mat = np.array(pd.DataFrame(mat).fillna(0))
    mean = np.nanmean(np.where(mat != 0, mat, np.nan), axis = 1)
    
    if(sim == 'COS'):
        Sim = COS(mat)
    elif(sim == 'PCC'):
        Sim = PCC(mat)
        
    k_neighbors = np.argsort(-Sim)
    k_neighbors = np.delete(k_neighbors, np.s_[k:], 1)
    
    NumUsers = np.size(mat, axis = 0)
    
    for u in range(0, NumUsers):
        list_sim = Sim[u, k_neighbors[u,]]
        list_rating = mat[k_neighbors[u,], ].astype('float64')
        list_mean = mean[k_neighbors[u, ],]
        denominator = np.sum(list_sim)
        numerator = np.sum(list_sim.reshape(-1, 1) * (list_rating - list_mean.reshape(-1, 1)), axis = 0)
        if denominator == 0 :
            predicted_rating[u, ] = 0
        else:
            predicted_rating[u, ] = mean[u] + numerator / denominator

    return predicted_rating


def basic_zscore(mat, sim, k):
    predicted_rating = np.array([[0.0 for col in range(mat.shape[1])] for row in range(mat.shape[0])])
    
    mat = np.array(pd.DataFrame(mat).fillna(0))
    mean = np.nanmean(np.where(mat != 0, mat, np.nan), axis = 1)
    std = np.nanstd(np.where(mat != 0, mat, np.nan), axis = 1)
    
    if(sim == 'COS'):
        Sim = COS(mat)
    elif(sim == 'PCC'):
        Sim = PCC(mat)
        
    k_neighbors = np.argsort(-Sim)
    k_neighbors = np.delete(k_neighbors, np.s_[k:], 1)
    
    NumUsers = np.size(mat, axis = 0)
    
    for u in range(0, NumUsers):
        list_sim = Sim[u, k_neighbors[u,]]#한줄
        list_rating = mat[k_neighbors[u,], ].astype('float64')#전체
        list_mean = mean[k_neighbors[u, ],]#한줄
        list_std = std[k_neighbors[u, ], ]#한줄
        #print(list_std.reshape(-1,1))
        denominator = np.sum(list_sim)
        
        arridx = np.where(list_std == 0)
        
        list_std[arridx] = 1
        list_sim[arridx] = 0
        
        #print(list_std)
        
        numerator = np.sum(list_sim.reshape(-1, 1) * ((list_rating - list_mean.reshape(-1, 1)) / list_std.reshape(-1,1)), axis = 0)
        
        if denominator == 0 :
            predicted_rating[u, ] = 0
        else:
            predicted_rating[u, ] = mean[u] + std[u] * numerator / denominator

    return predicted_rating



def basic_baseline(mat, sim, k):
    predicted_rating = np.array([[0.0 for col in range(mat.shape[1])] for row in range(mat.shape[0])])
    
    mat = np.array(pd.DataFrame(mat).fillna(0))
    user_mean = np.nanmean(np.where(mat != 0, mat, np.nan), axis = 1)
    item_mean = np.nanmean(np.where(mat != 0, mat, np.nan), axis = 0) #아이템 평균 배열
    
    all_avg = np.sum(mat)/(mat>0).sum() #모든 rating 평균
    
    if(sim == 'COS'):
        Sim = COS(mat)
    elif(sim == 'PCC'):
        Sim = PCC(mat)
        
    k_neighbors = np.argsort(-Sim)
    k_neighbors = np.delete(k_neighbors, np.s_[k:], 1)
    
    NumUsers = np.size(mat, axis = 0)
    
    baseline = user_mean.reshape(-1, 1) + item_mean - all_avg
    
    for u in range(0, NumUsers):
        list_sim = Sim[u, k_neighbors[u,]]
        list_rating = mat[k_neighbors[u,], ].astype('float64')    
        list_mean = user_mean[k_neighbors[u, ],]
        denominator = np.sum(list_sim)
        
        numerator = np.sum(list_sim.reshape(-1, 1) * (list_rating - baseline[u,]), axis = 0)
        
        if denominator == 0:
            predicted_rating[u, ] = 0
        else:
            predicted_rating[u, ] = (baseline[u,].reshape(1,-1) + (numerator / denominator).reshape(1,-1))

    return predicted_rating

