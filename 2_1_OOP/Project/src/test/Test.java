package test;

import csv.CSVs;
import csv.Column;
import csv.Table;

import java.io.File;
import java.io.FileNotFoundException;

public class Test {
    public static void main(String[] args) throws FileNotFoundException {
        Table anotherTable = null;

        File csv = new File("rsc/train.csv");

//        1) CSV 파일로부터 테이블 객체 생성
        Table table = CSVs.createTable(csv, true);

//        2) TableImple의 toString()을 override 한다.
//        System.out.println(table);

//        3) 테이블을 화면에 출력한다.
//        table.print();

//        4) 테이블의 컬럼별 통계량을 출력한다.
//        table.getStats().print();

//        5) 처음 5줄 출력 (새 테이블)
//        table.head().print();
//        anotherTable = table.head();
//        System.out.println("identity test for head(): " + (table.equals(anotherTable) ? "Fail" : "Pass"));

//        6) 지정한 처음 n줄 출력 (새 테이블)
//        table.head(10).print();
//        anotherTable = table.head(10);
//        System.out.println("identity test for head(n): " + (table.equals(anotherTable) ? "Fail" : "Pass"));

//        7) 마지막 5줄 출력 (새 테이블)
//        table.tail().print();
//        anotherTable = table.tail();
//        System.out.println("identity test for tail(): " + (table.equals(anotherTable) ? "Fail" : "Pass"));

//        8) 지정한 마지막 n줄 출력 (새 테이블)
//        table.tail(10).print();
//        anotherTable = table.tail(10);
//        System.out.println("identity test for tail(n): " + (table.equals(anotherTable) ? "Fail" : "Pass"));

//        9) 지정한 행 인덱스 범위(begin<=, <end)의 서브테이블을 얻는다. (새 테이블)
//        table.selectRows(0, 10).print();
//        anotherTable = table.selectRows(0, 10);
//        System.out.println("identity test for selectRows(range): " + (table.equals(anotherTable) ? "Fail" : "Pass"));

//        10) 지정한 행 인덱스로만 구성된 서브테이블을 얻는다. (새 테이블)
//        table.selectRowsAt(654, 829, 10, 99).print();
//        anotherTable = table.selectRowsAt(654, 829);
//        System.out.println("identity test for selectRowsAt(indices): " + (table.equals(anotherTable) ? "Fail" : "Pass"));

//        11) 지정한 열 인덱스 범위(begin<=, <end)의 서브테이블을 얻는다. (새 테이블)
//        table.selectColumns(0, 4).print();
//        anotherTable = table.selectColumns(0, 4);
//        System.out.println("identity test for selectColumns(range): " + (table.equals(anotherTable) ? "Fail" : "Pass"));

//        10) 지정한 열 인덱스로만 구성된 서브테이블을 얻는다. (새 테이블)
//        table.selectColumnsAt(4, 5, 3).print();
//        anotherTable = table.selectColumnsAt(4, 5, 3);
//        System.out.println("identity test for selectColumnsAt(indices): " + (table.equals(anotherTable) ? "Fail" : "Pass"));

//        11) 테이블을 기준 열인덱스(3)로 정렬한다. 이 때, 오름차순(true), null값은 나중에(false)(원본 테이블 정렬)
//        table.sort(5, true, false).print();
//        anotherTable = table.sort(5, true, false);
//        System.out.println("identity test for sort(index, asc, nullOrder): " + (!table.equals(anotherTable) ? "Fail" : "Pass"));

//        12) 테이블을 기준 열인덱스(3)로 정렬한다. 이 때, 내림차순(false), null값은 앞에(true)(새 테이블)
//        CSVs.sort(table, 10, false, true).print();
//        anotherTable = CSVs.sort(table, 10, false, true);
//        System.out.println("identity test for CSVs.sort(index, asc, nullOrder): " + (table.equals(anotherTable) ? "Fail" : "Pass"));

//        13) 테이블을 랜덤하게 섞는다. (원본 테이블은 유지, 랜덤하게 섞인 새 테이블 반환)
//        System.out.println("****************************** before shuffling ******************************");
//        table.print();
//        anotherTable = CSVs.shuffle(table);
//        System.out.println("****************************** after shuffling (copy)******************************");
//        anotherTable.print();
//        System.out.println("****************************** after shuffling (original)******************************");
//        table.print();
//        System.out.println("identity test for CSVs.shuffle(table): " + (table.equals(anotherTable) ? "Fail" : "Pass"));

//        14) 테이블을 랜덤하게 섞는다. (원본 테이블 섞임)
//        System.out.println("****************************** before shuffling ******************************");
//        table.print();
//        anotherTable = table.shuffle();
//        System.out.println("****************************** after shuffling (copy)******************************");
//        anotherTable.print();
//        System.out.println("****************************** after shuffling (original)******************************");
//        table.print();
//        System.out.println("identity test for shuffle(): " + (!table.equals(anotherTable) ? "Fail" : "Pass"));

//        15) null을 그 컬럼의 mean으로 치환 (원본 테이블 값 변경)
//        table.print();
//        int nullCount = 0;
//        for (int i = 0; i < table.getColumnCount(); i++) nullCount += table.getColumn(i).getNullCount();
//        System.out.println("(before) null count: " + nullCount);
//        System.out.println("(result) table.fillNullWithMean(): " + table.fillNullWithMean());
//        table.print();
//        nullCount = 0;
//        for (int i = 0; i < table.getColumnCount(); i++) nullCount += table.getColumn(i).getNullCount();
//        System.out.println("(after) null count: " + nullCount);

//        16) null을 0으로 치환 (원본 테이블 값 변경)
//        table.print();
//        int nullCount = 0;
//        for (int i = 0; i < table.getColumnCount(); i++) nullCount += table.getColumn(i).getNullCount();
//        System.out.println("(before) null count: " + nullCount);
//        System.out.println("(result) table.fillNullWithZero(): " + table.fillNullWithZero());
//        table.print();
//        nullCount = 0;
//        for (int i = 0; i < table.getColumnCount(); i++) nullCount += table.getColumn(i).getNullCount();
//        System.out.println("(after) null count: " + nullCount);

//        17) (가능한 컬럼에 대하여) table 컬럼마다 평균 0, 표준편차 1로 표준화한다 (원본 테이블 값 변경)
//        System.out.println("****************************** before standardization ******************************");
//        table.print();
//        System.out.println("table.standardize() = " + table.standardize());
//        System.out.println("****************************** after standardization ******************************");
//        table.print();
//        table.getStats().print();

//        18) (가능한 컬럼에 대하여) table 컬럼마다 min 0, max 1로 정규화한다 (원본 테이블 값 변경)
//        System.out.println("****************************** before normalization ******************************");
//        table.print();
//        System.out.println("table.normalize() = " + table.normalize());
//        System.out.println("****************************** after normalization ******************************");
//        table.print();
//        table.getStats().print();

//        19) (가능한 컬럼에 대하여) table 컬럼마다 값이 {0, 1}로 구성되게 한다. (원본 테이블 값 변경)
//        System.out.println("****************************** before factorizing ******************************");
//        table.print();
//        System.out.println("table.factorize() = " + table.factorize());
//        System.out.println("****************************** after factorizing ******************************");
//        table.print();

//        20) 조건식을 만족하는 행을 얻는다.
//        table.selectRowsBy("Name", (String x) -> x.contains("Lee")).print();
//        table.selectRowsBy("Age", (Integer x) -> x < 20).print();
//        table.selectRowsBy("Fare", (Double x) -> x < 20).print();
//        table.selectRowsBy("Cabin", (String x) -> x.length() < 3).print();
//        table.selectRowsBy("Age", (Object x) -> x == null).print();

//        ****************************** test for Column ******************************
//        System.out.println("*** before setValue(index, T value)");
//        int columnIndex = (int) (Math.random() * table.getColumnCount());
//        int rowIndex = (int) (Math.random() * table.getColumn(columnIndex).count());
//        String columnName = table.getColumn(columnIndex).getHeader();
//        table.selectRowsAt(rowIndex).print();
//        table.getColumn(columnName).setValue(rowIndex, "Sample");
//        System.out.println("Column " + columnName + "has been changed");
//        System.out.println("*** after setValue(index, T value)");
//        table.selectRowsAt(rowIndex).print();

//        System.out.println("*** before getValue(index, T value)");
//        int columnIndex = (int) (Math.random() * table.getColumnCount());
//        int rowIndex = (int) (Math.random() * table.getColumn(columnIndex).count());
//        String columnName = table.getColumn(columnIndex).getHeader();
//        table.selectRowsAt(rowIndex).print();
//        int value = table.getColumn(columnName).getValue(rowIndex, Integer.class);
//        System.out.println("The value in (" + rowIndex + ", " + columnIndex + ") is " + value);
    }
}
