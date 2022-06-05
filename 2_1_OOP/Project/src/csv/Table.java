package csv;

import java.util.function.Predicate;

public interface Table {
    void print();

    /**
     * String 타입 컬럼이더라도,
     * 그 컬럼에 double로 처리할 수 있는 값이 있다면,
     * 그 값을 대상으로 해당 컬럼 통계량을 산출
     */
    Table getStats();

    /**
     * @return 처음 (최대)5개 행으로 구성된 새로운 Table 생성 후 반환
     */
    Table head();
    /**
     * @return 처음 (최대)lineCount개 행으로 구성된 새로운 Table 생성 후 반환
     */
    Table head(int lineCount);

    /**
     * @return 마지막 (최대)5개 행으로 구성된 새로운 Table 생성 후 반환
     */
    Table tail();
    /**
     * @return 마지막 (최대)lineCount개 행으로 구성된 새로운 Table 생성 후 반환
     */
    Table tail(int lineCount);

    /**
     * @param beginIndex 포함(이상)
     * @param endIndex 미포함(미만)
     * @return 검색 범위에 해당하는 행으로 구성된 새로운 Table 생성 후 반환
     */
    Table selectRows(int beginIndex, int endIndex);

    /**
     * @return 검색 인덱스에 해당하는 행으로 구성된 새로운 Table 생성 후 반환
     */
    Table selectRowsAt(int ...indices);

    /**
     * @param beginIndex 포함(이상)
     * @param endIndex 미포함(미만)
     * @return 검색 범위에 해당하는 열로 구성된 새로운 Table 생성 후 반환
     */
    Table selectColumns(int beginIndex, int endIndex);

    /**
     * @return 검색 인덱스에 해당하는 열로 구성된 새로운 Table 생성 후 반환
     */
    Table selectColumnsAt(int ...indices);

    /**
     * @param
     * @return 검색 조건에 해당하는 행으로 구성된 새로운 Table 생성 후 반환, 제일 나중에 구현 시도하세요.
     */
    <T> Table selectRowsBy(String columnName, Predicate<T> predicate);

    /**
     * @return 원본 Table이 정렬되어 반환된다.
     */
    Table sort(int byIndexOfColumn, boolean isAscending, boolean isNullFirst);

    /**
     * @return 원본 Table이 무작위로 뒤섞인 후 반환된다. 말 그대로 랜덤이어야 한다. 즉, 랜덤 로직이 존재해야 한다.
     */
    Table shuffle();

    int getRowCount();
    int getColumnCount();

    /**
     * @return 원본 Column이 반환된다. 따라서, 반환된 Column에 대한 조작은 원본 Table에 영향을 끼친다.
     */
    Column getColumn(int index);
    /**
     * @return 원본 Column이 반환된다. 따라서, 반환된 Column에 대한 조작은 원본 Table에 영향을 끼친다.
     */
    Column getColumn(String name);

    /**
     * String 타입 컬럼들에는 영향을 끼치지 않는다.
     * double 혹은 int 타입 컬럼들에 한해서 null 값을 mean 값으로 치환한다.
     * 이 연산 후, int 타입 컬럼에 mean으로 치환된 cell이 있을 경우, 이 컬럼은 double 타입 컬럼으로 바뀐다.
     * 왜냐하면, mean 값이 double이기 때문이다.
     * @return 테이블에 mean으로 치환한 cell이 1개라도 발생했다면, true 반환
     */
    boolean fillNullWithMean();

    /**
     * String 타입 컬럼들에는 영향을 끼치지 않는다.
     * double 혹은 int 타입 컬럼들에 한해서 null 값을 0으로 치환한다.
     * 이 연산 후, int 타입 혹은 double 타입 컬럼 모두 그 타입이 유지된다.
     * @return 테이블에 0으로 치환한 cell이 1개라도 발생했다면, true 반환
     */
    boolean fillNullWithZero();

    /**
     * 평균 0, 표준편자 1인 컬럼으로 바꾼다. (null은 연산 후에도 null로 유지된다. 즉, null은 연산 제외)
     * String 타입 컬럼들에는 영향을 끼치지 않는다.
     * double 혹은 int 타입 컬럼들에 한해서 수행된다.
     * 이 연산 후, int 타입 컬럼은 double 타입 컬럼으로 바뀐다.
     * 왜냐하면, mean과 std가 double이기 때문이다.
     * @return 이 연산에 의해 값이 바뀐 열이 1개라도 발생했다면, true 반환
     */
    boolean standardize();

    /**
     * 최솟값 0, 최댓값 1인 컬럼으로 바꾼다. (null은 연산 후에도 null로 유지된다.즉, null은 연산 제외)
     * String 타입 컬럼들에는 영향을 끼치지 않는다.
     * double 혹은 int 타입 컬럼들에 한해서 수행된다.
     * 이 연산 후, int 타입 컬럼은 double 타입 컬럼으로 바뀐다.
     * 왜냐하면, 0과 1사이의 값들은 double이기 때문이다.
     * @return 이 연산에 의해 값이 바뀐 열이 1개라도 발생했다면, true 반환
     */
    boolean normalize();


    /**
     * null을 제외하고 2가지 값으로만 구성된 컬럼이기만 하면 수행된다.
     * 연산 후 0과 1로 구성된 컬럼으로 바뀐다. (null은 연산 후에도 null로 유지된다.즉, null은 연산 제외)
     * 모든 타입 컬럼들에 대해서 수행될 수 있다.
     * 이 연산이 수행된 컬럼은 int 타입 컬럼으로 바뀐다.
     * 왜냐하면, 0과 1이 int이기 때문이다.
     * @return 이 연산에 의해 값이 바뀐 열이 1개라도 발생했다면, true 반환
     */
    boolean factorize();
}
