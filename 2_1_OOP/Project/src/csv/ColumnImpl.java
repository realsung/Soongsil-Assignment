package csv;

import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

class ColumnImpl implements Column{
	List<String> columnList;
	String header;
	
	ColumnImpl(){
		this.columnList = new ArrayList<>();
	}
	
	ColumnImpl(String header){
		this();
		this.header = header;
	}
	
	ColumnImpl(List<String> l){
		this();
		this.columnList.addAll(l);
	}
	
	ColumnImpl(List<String> l, String header){
		this(l);
		this.header = header;
	}
	
    String getDtype(){
        String type = "int";
		try {
			for (int i = 0; i < columnList.size(); i++) {
				if(columnList.get(i) == null || columnList.get(i).equals("")) continue;
				Integer.parseInt(columnList.get(i));
			}
		} catch (NumberFormatException e){
			try{
				type = "double";
				for(int i=0; i<columnList.size(); i++){
					try {
						if(columnList.get(i) == null || columnList.get(i).equals("")) continue;
						Double.parseDouble(columnList.get(i));
					} catch (NullPointerException n){
						type = "String";
					}
				}
				type = "double";
			}
			catch (NumberFormatException e2){
				type = "String";
			}
		}
		return type;
    }

	long getColumnWidth(){
		long maxLength = 0;
		if(header != null){
			maxLength = header.length();
		}
		for(String str: columnList){
			if(str.length() > maxLength){
				maxLength = str.length();
			}
		}
		return maxLength;
	}
    
    void addData(String data) {
    	this.columnList.add(data);
    }

	double Percentile(double percentile, List<Double> l){
		double index = percentile*(l.size()-1);
		int lower = (int)Math.floor(index);
		if(lower<0){
			return l.get(0);
		}
		if(lower>=l.size()-1){
			return l.get(l.size()-1);
		}
		double fraction = index-lower;
		double result=l.get(lower) + fraction*(l.get(lower+1)-l.get(lower));
		return result;
	}
    
	@Override
	public String getHeader() {
		return header;
	}

	@Override
	public String getValue(int index) {
//		if(columnList.isEmpty()) return null;
		if(columnList.get(index).equals("")) return "null";
		return columnList.get(index);
	}

	@Override
	public <T extends Number> T getValue(int index, Class<T> t) {
		if(t == Integer.class) {
            return t.cast(Integer.parseInt(this.columnList.get(index)));   
		}
        else if(t == Double.class) {
            return t.cast(Double.parseDouble(this.columnList.get(index)));
        }
		return null;
	}

	@Override
	public void setValue(int index, String value) {
		columnList.set(index, value);
	}

	@Override
	public <T extends Number> void setValue(int index, T value) {
		columnList.set(index, value.toString());
	}

	@Override
	public int count() {
		return columnList.size();
	}

	@Override
	public void print() {
		// TODO Auto-generated method stub
		
	}
    
	@Override
	public boolean isNumericColumn() {
		for(String str : columnList) {
			if(str.equals("") || str.equals("null")) continue;
			try {
				Double.parseDouble(str);
			}catch(NumberFormatException e) {
				return false;
			}	
		}
		return true;
	}

	@Override
	public long getNullCount() {
		long cnt = 0;
		for(int i=0; i<columnList.size(); i++) {
			if(columnList.get(i).isEmpty())
				cnt++;
		}
		return cnt;
	}

	@Override
	public long getNumericCount() {
		long cnt = 0;
		for(String str: columnList) {
			if(str.equals("null")) continue;
			try {
				Double.parseDouble(str);
				cnt++;
			}catch(NumberFormatException e) {
			
			}
		}
		return cnt;
	}

	@Override
	public double getNumericMin() {
//		List<Double> l = new ArrayList<>();
		double tmp;
		double min = 0;
		boolean check = false;
		for(String str: columnList) {
			if(str.equals("null")) continue;
			try {
				tmp = Double.parseDouble(str);
				if(!check) {
					min = tmp;
					check = true;
				}
				if(min > tmp) min = tmp;
//				l.add(tmp);
			}catch(NumberFormatException e) {
			
			}
		}
		return min;
//		return Collections.min(l);
	}

	@Override
	public double getNumericMax() {
//		List<Double> l = new ArrayList<>();
		double tmp;
		double max = 0;
		for(String str: columnList) {
			if(str.equals("null")) continue;
			try {
				tmp = Double.parseDouble(str);
				if(tmp > max) max = tmp; 
//				l.add(tmp);
			}catch(NumberFormatException e) {
			
			}
		}
		return max;
//		return Collections.max(l);
	}

	@Override
	public double getMean() {
		double sum = 0;
		int cnt = 0;
		double result;
		for(String str: columnList) {
			if(str.equals("null")) continue;
			try {
				sum += Double.parseDouble(str);
				cnt++;
			}catch(NumberFormatException e) {
			
			}
		}
		result = Math.round((sum / cnt * 1000000)) / 1000000.0;
		return result;
	}
    
	@Override
	public double getStd() {
		double sum = 0;
		double mean = getMean();
		double result;

		for (String str : columnList) {
			if(str.equals("null")) continue;
			try {
				sum += Math.pow(Double.parseDouble(str) - mean, 2);
			} catch (NumberFormatException e) {

			}
		}
		result = Math.round((Math.sqrt(sum / (getNumericCount() - 1)) * 1000000)) / 1000000.0;
		return result;
	}

	@Override
	public double getQ1() {
		List<Double> l = new ArrayList<>();
		for(String str: columnList) {
			if(str.equals("null")) continue;
			try {
				l.add(Double.parseDouble(str));
			}catch(NumberFormatException e) {

			}
		}
		Collections.sort(l);
		return Percentile(0.25, l);
	}

	@Override
	public double getMedian() {
		List<Double> l = new ArrayList<>();
		for(String str: columnList) {
			if(str.equals("null")) continue;
			try {
				l.add(Double.parseDouble(str));
			}catch(NumberFormatException e) {
			
			}
		}
		Collections.sort(l);
		return Percentile(0.5, l);
	}

	@Override
	public double getQ3() {
		List<Double> l = new ArrayList<>();
		for(String str: columnList) {
			if(str.equals("null")) continue;
			try {
				l.add(Double.parseDouble(str));
			}catch(NumberFormatException e) {

			}
		}
		Collections.sort(l);
		return Percentile(0.75, l);
	}

	@Override
	public boolean fillNullWithMean() {
		boolean flag = false;
		double meanValue = getMean();
		if(getNumericCount() == 0) return false;
		for(int i = 0; i < count(); i++) {
			if(getValue(i).equals("null")) {
				if(!flag) flag = true;
				setValue(i, meanValue);
			}
		}
		return flag;
	}

	@Override
	public boolean fillNullWithZero() {
		boolean flag = false;
		if(getNumericCount() == 0) return false;
		for(int i = 0; i < count(); i++) {
			if(getValue(i).equals("null")) {
				if(!flag) flag = true;
				setValue(i, 0);
			}
		}
		return flag;
	}

	@Override
	public boolean standardize() {
		if (!isNumericColumn()) return false;
		boolean flag = false;
		double std = getStd();
		double mean = getMean();
		double tmp;
		System.out.println(this.header + " : " + getDtype());
		if(!getDtype().equals("String")){
			flag = true;
			for(int i=0; i<count(); i++){
				try{
					if(this.columnList.get(i).equals("null")) continue;
					tmp = Math.round(((Double.parseDouble(this.columnList.get(i)) - mean) / std) * 1000000) / 1000000.0;
					setValue(i, Double.toString(tmp));
				}catch(NumberFormatException e){

				}
			}
		}
		return flag;
	}

	@Override
	public boolean normalize() {
		boolean flag = false;
		double max = getNumericMax();
		double min = getNumericMin();
		double tmp;
		
		if(!getDtype().equals("String")){
			flag = true;
			for(int i=0; i<count(); i++){
				try{
					if(this.columnList.get(i).equals("null")) continue;
					tmp = Math.round(((Double.parseDouble(this.columnList.get(i)) - min) / (max - min)) * 1000000) / 1000000.0;
					setValue(i, Double.toString(tmp));
				}catch(NumberFormatException e){

				}
			}
		}

		return flag;
	}

	@Override
	public boolean factorize() {
		int cnt = 0;
		boolean flag = false;
		List<String> table = new ArrayList<>();
		String tmp;
		for(int i=0; i<count(); i++) {
			tmp = this.columnList.get(i);
			if(tmp.equals("null")) continue;
			if(table.contains(tmp)) {
				if(cnt >= 3) {
					return flag;
				}
			}else {
				table.add(tmp);
				cnt++;
			}
		}
		if(cnt == 2) {
			flag = true;
			for(int i=0; i<count(); i++){
				tmp = this.columnList.get(i);
				if(tmp.equals("null")) continue;
				else if(table.get(0).equals(tmp)) {
					setValue(i, "1");
				}else if(table.get(1).equals(tmp)) {
					setValue(i, "0");
				}
			}
		}
		return flag;
	}

}
