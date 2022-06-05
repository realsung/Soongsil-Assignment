package csv;

public interface Column {
    String getHeader();

    /* cell 값을 String으로 반환 */
    String getValue(int index);

    /**
     * @param index
     * @param t 가능한 값으로 Double.class, Integer.class
     * @return Double 혹은 Integer로 반환 불가능할 시, 예외 발생
     */
    <T extends Number> T getValue(int index, Class<T> t);

    void setValue(int index, String value);

    /**
     * @param value double, int 리터럴을 index의 cell로 건네고 싶을 때 사용
     */
    <T extends Number> void setValue(int index, T value);

    /**
     * @return null 포함 모든 cell 개수 반환
     */
    int count();

    void print();

    /**
     * @return (int or null)로 구성된 컬럼 or (double or null)로 구성된 컬럼이면 true 반환
     */
    boolean isNumericColumn();

    long getNullCount();

    /**
     * @return int 혹은 double로 평가될 수 있는 cell의 개수
     */
    long getNumericCount();

    // 아래 7개 메소드는 String 타입 컬럼에 대해서 수행 시, 예외 발생 시켜라.
    double getNumericMin();
    double getNumericMax();
    double getMean();
    double getStd();
    double getQ1();
    double getMedian();
    double getQ3();

    // 아래 2개 메소드는 1개 cell이라도 치환했으면, true 반환.
    boolean fillNullWithMean();
    boolean fillNullWithZero();

    // 아래 3개 메소드는 null 값은 메소드 호출 후에도 여전히 null.
    // standardize()와 normalize()는 String 타입 컬럼에 대해서는 false 반환
    // factorize()는 컬럼 타입과 무관하게 null 제외하고 2가지 값만으로 구성되었다면 수행된다. 조건에 부합하여 수행되었다면 true 반환
    boolean standardize();
    boolean normalize();
    boolean factorize();
}
