#pragma once
#include "Header.h"
#include "matrix.h"
#include "MyFunction.h"

void menuLab_3();
void info2();
void writeMatrixTxt(Matrix &matrix);
// void readMatrixTxt();
void replaceEl(Matrix &matrix);
Matrix createMatrix(size_t, size_t);
void solution(Matrix &matrix);
// void clearMatrix();
// void inpMatirxEl();

void outTableMatrixGraf(HDC hdc,
						double **matrix, // ������� ����� double
						size_t rows, size_t cols,
						int startX, int startY,		   // ��������� ���������� �������
						int cellWidth, int cellHeight, // ������� ������
						int headerFontSize,			   // ������ ������ ����������
						int dataFontSize);