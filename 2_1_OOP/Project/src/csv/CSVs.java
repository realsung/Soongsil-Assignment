package csv;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class CSVs {
    /**
     * @param isFirstLineHeader csv 파일의 첫 라인을 헤더(타이틀)로 처리할까요?
     */
    public static Table createTable(File csv, boolean isFirstLineHeader) throws FileNotFoundException {
    	try {
        	FileReader fr = new FileReader(csv);
        	BufferedReader br = new BufferedReader(fr);
        	ColumnImpl col = new ColumnImpl();
        	List<List<String>> columnList = new ArrayList<>();
        	List<String> line = new ArrayList<>();
        	String t;
        	String[] readLineTemp;
        	String tmp;
        	if(isFirstLineHeader) {
        		for(String i: br.readLine().split(","))
            		line.add(i);
            	columnList.add(line);
        	}else {
        		br.readLine();
        	}
        	
        	while((t = br.readLine()) != null) {
        		readLineTemp = t.split(",(?=(?:[^\\\"]*\\\"[^\\\"]*\\\")*[^\\\"]*$)", -1);
        		List<String> line2 = new ArrayList<>();
        		for(String i: readLineTemp) {
        			tmp = i;
        			if(i.startsWith("\"") && i.endsWith("\"")) 
        				tmp = tmp.substring(1, tmp.length()-1).replaceAll("\"\"", "\"");
        			line2.add(tmp);
        		}
        		columnList.add(line2);
        	}
        	TableImpl table = new TableImpl(columnList, isFirstLineHeader);
        	return table;
    	}catch(IOException e) {
    		e.printStackTrace();
    		System.out.println(e.getMessage());
    		return null;
    	}
    }

    /**
     * @return 새로운 Table 객체를 반환한다. 즉, 첫 번째 매개변수 Table은 변경되지 않는다.
     */
    public static Table sort(Table table, int byIndexOfColumn, boolean isAscending, boolean isNullFirst) {
		return table.selectRows(0, table.getRowCount()).sort(byIndexOfColumn, isAscending, isNullFirst);
    }

    /**
     * @return 새로운 Table 객체를 반환한다. 즉, 첫 번째 매개변수 Table은 변경되지 않는다.
     */
    public static Table shuffle(Table table) {
        return table.selectRows(0, table.getRowCount()).shuffle();
    }
}
