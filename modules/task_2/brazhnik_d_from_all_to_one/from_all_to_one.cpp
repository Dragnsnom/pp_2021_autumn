// Copyright 2021 Brazhnik Dmitry
#include "../../../modules/task_2/brazhnik_d_from_all_to_one/from_all_to_one.h"

std::vector<int> fillRandomValToVectorInt(const int size) {
    std::vector<int> data(size);
    for (int i = 0; i < size; i++) {
        data[i] = getRandVal();
    }
    return data;
}

std::vector<double> fillRandomValToVectorDouble(const int size) {
    std::vector<double> data(size);
    for (int i = 0; i < size; i++) {
        data[i] = getRandValDouble();
    }
    return data;
}

std::vector<float> fillRandomValToVectorFloat(const int size) {
    std::vector<float> data(size);
    for (int i = 0; i < size; i++) {
        data[i] = getRandValFloat();
    }
    return data;
}

int getRandVal() {
    std::random_device dev;
    std::mt19937 gen(dev());
    return gen() % 100;
}

double getRandValDouble() {
    std::random_device dev;
    std::mt19937 gen(dev());
    return gen() % 100;
}

float getRandValFloat() {
    std::random_device dev;
    std::mt19937 gen(dev());
    return gen() % 100;
}

int customReduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm) {
    int countProc, commRank;
    MPI_Comm_size(comm, &countProc);
    MPI_Comm_rank(comm, &commRank);

    if (sendbuf == nullptr)
        return -1;
    if (count == 0)
        return -2;

    if (commRank != root) {
        MPI_Send(sendbuf, count, datatype, root, 0, comm);
    }

    if (commRank == root) {
        switch (datatype) {
        case MPI_INT:
            for (int i = 0; i < count; i++) {
                switch (op) {
                case MPI_SUM:
                    reinterpret_cast<int*>(recvbuf)[i] = 0;
                    break;
                case MPI_PROD:
                    reinterpret_cast<int*>(recvbuf)[i] = 1;
                    break;
                case MPI_MAX:
                    reinterpret_cast<int*>(recvbuf)[i] = -1;
                    break;
                case MPI_MIN:
                    reinterpret_cast<int*>(recvbuf)[i] = 101;
                    break;
                }
            }
            for (int i = 0; i < countProc; i++) {
                if (i != root)
                    MPI_Recv(sendbuf, count, datatype, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);

                for (int i = 0; i < count; i++) {
                    switch (op) {
                    case MPI_SUM:
                        reinterpret_cast<int*>(recvbuf)[i] += reinterpret_cast<int*>(sendbuf)[i];
                        break;
                    case MPI_PROD:
                        reinterpret_cast<int*>(recvbuf)[i] *= reinterpret_cast<int*>(sendbuf)[i];
                        break;
                    case MPI_MAX:
                        if (reinterpret_cast<int*>(recvbuf)[i] < reinterpret_cast<int*>(sendbuf)[i])
                            reinterpret_cast<int*>(recvbuf)[i] = reinterpret_cast<int*>(sendbuf)[i];
                        break;
                    case MPI_MIN:
                        if (reinterpret_cast<int*>(recvbuf)[i] > reinterpret_cast<int*>(sendbuf)[i])
                            reinterpret_cast<int*>(recvbuf)[i] = reinterpret_cast<int*>(sendbuf)[i];
                        break;
                    }
                }
            }
            break;
        case MPI_DOUBLE:
            for (int i = 0; i < count; i++) {
                switch (op) {
                case MPI_SUM:
                    reinterpret_cast<double*>(recvbuf)[i] = 0.0;
                    break;
                case MPI_PROD:
                    reinterpret_cast<double*>(recvbuf)[i] = 1.0;
                    break;
                case MPI_MAX:
                    reinterpret_cast<double*>(recvbuf)[i] = -1.0;
                    break;
                case MPI_MIN:
                    reinterpret_cast<double*>(recvbuf)[i] = 101.0;
                    break;
                }
            }

            for (int k = 0; k < countProc; k++) {
                if (k != root)
                    MPI_Recv(sendbuf, count, datatype, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);

                for (int i = 0; i < count; i++) {
                    switch (op) {
                    case MPI_SUM:
                        reinterpret_cast<double*>(recvbuf)[i] += reinterpret_cast<double*>(sendbuf)[i];
                        break;
                    case MPI_PROD:
                        reinterpret_cast<double*>(recvbuf)[i] *= reinterpret_cast<double*>(sendbuf)[i];
                        break;
                    case MPI_MAX:
                        if (reinterpret_cast<double*>(recvbuf)[i] < reinterpret_cast<double*>(sendbuf)[i])
                            reinterpret_cast<double*>(recvbuf)[i] = reinterpret_cast<double*>(sendbuf)[i];
                        break;
                    case MPI_MIN:
                        if (reinterpret_cast<double*>(recvbuf)[i] > reinterpret_cast<double*>(sendbuf)[i])
                            reinterpret_cast<double*>(recvbuf)[i] = reinterpret_cast<double*>(sendbuf)[i];
                        break;
                    }
                }
            }
            break;
        case MPI_FLOAT:
            for (int i = 0; i < count; i++) {
                switch (op) {
                case MPI_SUM:
                    reinterpret_cast<float*>(recvbuf)[i] = 0.0f;
                    break;
                case MPI_PROD:
                    reinterpret_cast<float*>(recvbuf)[i] = 1.0f;
                    break;
                case MPI_MAX:
                    reinterpret_cast<float*>(recvbuf)[i] = -1.0f;
                    break;
                case MPI_MIN:
                    reinterpret_cast<float*>(recvbuf)[i] = 101.0;
                    break;
                }
            }
            for (int k = 0; k < countProc; k++) {
                if (k != root)
                    MPI_Recv(sendbuf, count, datatype, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);

                for (int i = 0; i < count; i++) {
                    switch (op) {
                    case MPI_SUM:
                        reinterpret_cast<float*>(recvbuf)[i] += reinterpret_cast<float*>(sendbuf)[i];
                        break;
                    case MPI_PROD:
                        reinterpret_cast<float*>(recvbuf)[i] *= reinterpret_cast<float*>(sendbuf)[i];
                        break;
                    case MPI_MAX:
                        if (reinterpret_cast<float*>(recvbuf)[i] < reinterpret_cast<float*>(sendbuf)[i])
                            reinterpret_cast<float*>(recvbuf)[i] = reinterpret_cast<float*>(sendbuf)[i];
                        break;
                    case MPI_MIN:
                        if (reinterpret_cast<float*>(recvbuf)[i] > reinterpret_cast<float*>(sendbuf)[i])
                            reinterpret_cast<float*>(recvbuf)[i] = reinterpret_cast<float*>(sendbuf)[i];
                        break;
                    }
                }
            }
            break;
        default:
            return -1;
            break;
        }
    }
    return 0;
}
