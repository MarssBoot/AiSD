#include<iostream>
#include<string>
#include<locale.h>

#include"TDatList.h"
#include"TDatLink.h"
#include"TDatValue.h"
#include"TItemValue.h"

using namespace std;

TDatList* createTestList() {
	int elemsCount = 5;
	TDatValue** listElems = new TDatValue*[elemsCount];
	TItemValue* pVal;
	for (int i = 0; i < elemsCount; i++)
	{
		pVal = new TItemValue(10 * i);
		listElems[i] = pVal;
	}
	TDatList* pList = new TDatList(listElems, elemsCount);
	return pList;
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	cout << "������������ ������..." << endl;
	{
		cout << "���� 1. ������ ������" << endl;
		TDatList list;
		cout << "1.1. list.GetDatValue(FIRST) == nullptr. Expected: " << true << ", actual: " << (list.GetValue(0) == nullptr) << endl;
		cout << "1.2. list.GetDatValue(LAST) == nullptr. Expected: " << true << ", actual: " << (list.GetValue(2) == nullptr) << endl;
		cout << "1.3. list.GetDatValue(CURRENT) == nullptr. Expected: " << true << ", actual: " << (list.GetValue(1) == nullptr) << endl;
		cout << "1.4. list.GetListLength(). Expected: " << 0 << ", actual: " << list.GetListLen() << endl;
		cout << "1.5. list.IsEmpty(). Expected: " << true << ", actual: " << list.IsEmpty() << endl;
		cout << endl;
	}
	{
		cout << "���� 2. ������ {0, 10, 20, 30, 40}" << endl;

		TDatList* pList = createTestList();
		cout << *(pList) << endl;
		cout << pList->GetCurrPos() << endl;

		int firstVal = ((TItemValue*)pList->GetValue(0))->GetValue();
		int lastVal = ((TItemValue*)pList->GetValue(2))->GetValue();
		int currentVal = ((TItemValue*)pList->GetValue(1))->GetValue();

		cout << "2.1. ������ �������. Expected: " << 0 << ", actual: " << firstVal << endl;
		cout << "2.2. ��������� �������. Expected: " << 40 << ", actual: " << lastVal << endl;
		cout << "2.3. ������� �������. Expected: " << 0 << ", actual: " << currentVal << endl;
		cout << "2.4. pList->GetListLength(). Expected: " << 5 << ", actual: " << pList->GetListLen() << endl;
		cout << "2.5. pList->IsEmpty(). Expected: " << false << ", actual: " << pList->IsEmpty() << endl;
		cout << "2.6. pList->GetCurrentPos(). Expected: " << 0 << ", actual: " << pList->GetCurrPos() << endl;
		cout << "2.7. pList->IsListEnded(). Expected: " << false << ", actual: " << pList->IsListEnded() << endl; // ���� ����� � ���� ���������� � ������ �������(�������� ���������� � TDatList.h)

		cout << "2.8. ������ ������: " << *pList << endl;

		delete pList;
		cout << endl;
	}
	{
		cout << "���� 3. SetCurrentPos()/GetCurrentPos()/Reset()" << endl;

		TDatList* pList = createTestList();

		pList->SetCurrPos(2);
		int currentVal = ((TItemValue*)pList->GetValue(1))->GetValue();

		cout << "3.1. ������� �������. Expected: " << 2 << ", actual: " << pList->GetCurrPos() << endl;
		cout << "3.2. ������� �������. Expected: " << 20 << ", actual: " << currentVal << endl;

		pList->Reset();
		currentVal = ((TItemValue*)pList->GetValue(1))->GetValue();

		cout << "����� pList->Reset()" << endl;
		cout << "3.3. ������� �������. Expected: " << 0 << ", actual: " << pList->GetCurrPos() << endl;
		cout << "3.4. ������� �������. Expected: " << 0 << ", actual: " << currentVal << endl;

		delete pList;
		cout << endl;
	}
	{
		cout << "���� 4. GoNext()/IsListEnded()" << endl;

		TDatList* pList = createTestList();

		pList->GoNext();
		int currentVal = ((TItemValue*)pList->GetValue(1))->GetValue();

		cout << "����� pList->GoNext() x1" << endl;
		cout << "4.1. ������� �������. Expected: " << 1 << ", actual: " << pList->GetCurrPos() << endl;
		cout << "4.2. ������� �������. Expected: " << 10 << ", actual: " << currentVal << endl;
		cout << "4.3. ����� ������? Expected: " << false << ", actual: " << pList->IsListEnded() << endl; // ���� ����� � ���� ���������� � ������ �������(�������� ���������� � TDatList.h)

		pList->GoNext();
		pList->GoNext();
		pList->GoNext();
		currentVal = ((TItemValue*)pList->GetValue(1))->GetValue();

		cout << "����� pList->GoNext() x3" << endl;
		cout << "4.4. ������� �������. Expected: " << 4 << ", actual: " << pList->GetCurrPos() << endl;
		cout << "4.5. ������� �������. Expected: " << 40 << ", actual: " << currentVal << endl;
		cout << "4.6. ����� ������? Expected: " << false << ", actual: " << pList->IsListEnded() << endl;

		pList->GoNext();

		cout << "����� ��� ������ ������ pList->GoNext() ������ ������ �����������" << endl;
		cout << "4.7. ����� ������? Expected: " << true << ", actual: " << pList->IsListEnded() << endl;

		delete pList;
		cout << endl;
	}
	{
		cout << "���� 5. �������/�������� ������� {0, 10, 20, 30, 40}" << endl;

		TDatList* pList = createTestList();
		pList->SetCurrPos(2);

		TDatValue* pVal = new TItemValue(11);
		pList->InsCurrent(pVal);
		int currentVal = ((TItemValue*)pList->GetValue(1))->GetValue();
		cout << "������� �� ������� ������� (2) �������� (11)" << endl;
		cout << "5.1. ������� �������. Expected: " << 2 << ", actual: " << pList->GetCurrPos() << endl;
		cout << "5.2. ������� �������. Expected: " << 11 << ", actual: " << currentVal << endl;

		pVal = new TItemValue(12);
		pList->InsFirst(pVal);
		int firstVal = ((TItemValue*)pList->GetValue(0))->GetValue();
		cout << "������� � ������ �������� (12)" << endl;
		cout << "5.3. ������ �������. Expected: " << 12 << ", actual: " << firstVal << endl;

		pVal = new TItemValue(13);
		pList->InsLast(pVal);
		int lastVal = ((TItemValue*)pList->GetValue(2))->GetValue();
		cout << "������� � ����� �������� (13)" << endl;
		cout << "5.4. ��������� �������. Expected: " << 13 << ", actual: " << lastVal << endl;

		cout << endl << "5.5. ������������� ������ ������." << endl;
		cout << "Expected: 12 0 10 11 20 30 40 13 " << endl;
		cout << "Actual:   " << *pList << endl << endl;

		pList->SetCurrPos(0);
		pList->DelCurrent();
		cout << "������������� ������� ������� 0, ������� ������� �������" << endl;
		cout << "5.6. ������������� ������ ������." << endl;
		cout << "Expected: 0 10 11 20 30 40 13 " << endl;
		cout << "Actual:   " << *pList << endl << endl;

		pList->SetCurrPos(pList->GetListLen() - 1);
		pList->DelCurrent();
		cout << "������������� ������� ������� pList->GetListLength() - 1, ������� ������� �������" << endl;
		cout << "5.7. ������������� ������ ������." << endl;
		cout << "Expected: 0 10 11 20 30 40 " << endl;
		cout << "Actual:   " << *pList << endl << endl;

		pList->DelFirst();
		cout << "������� ������ �������" << endl;
		cout << "5.8. ������������� ������ ������." << endl;
		cout << "Expected: 10 11 20 30 40 " << endl;
		cout << "Actual:   " << *pList << endl << endl;

		pList->DelList();
		cout << "������� ���� ������" << endl;
		cout << "5.9. ������������� ������ ������ (������ ������ ���� ����)." << endl;
		cout << "Expected: " << endl;
		cout << "Actual:   " << *pList << endl << endl;

		delete pList;
		cout << endl;
	}
	{
		cout << "���� 6. �������/�������� ������� (������ ������)" << endl;

		TDatList list;

		TDatValue* pVal1 = new TItemValue(14);
		TDatValue* pVal2 = new TItemValue(15);
		TDatValue* pVal3 = new TItemValue(16);
		list.InsFirst(pVal1);
		list.InsLast(pVal2);
		list.InsCurrent(pVal3);

		cout << "��������� InsFirst(14), InsLast(15), InsCurrent(16)" << endl;
		cout << "6.1. ������������� ������ ������." << endl;
		cout << "Expected: 16 14 15 " << endl;
		cout << "Actual:   " << list << endl << endl;

		list.DelList();

		cout << "������� ���� ������" << endl;
		cout << "6.2. ������������� ������ ������ (������ ������ ���� ����)." << endl;
		cout << "Expected: " << endl;
		cout << "Actual:   " << list << endl << endl;

		cout << endl;
	}
}