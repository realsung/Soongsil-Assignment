package csv;

import java.util.Collections;
import java.util.function.Predicate;
import java.util.ArrayList;
import java.util.List;

class TableImpl implements Table{

	private List<ColumnImpl> colTable;
	
	TableImpl(){ }
	
	TableImpl(List<ColumnImpl> colList){
		this.colTable = colList;
	}
	
	TableImpl(List<List<String>> columnList, boolean isFirstLineHeader) {
		this.colTable = new ArrayList<ColumnImpl>();
		List<String> tmp = new ArrayList<String>();
		for(int i=0; i<columnList.get(0).size(); i++) {
			if(isFirstLineHeader) {
				for(int j=1; j<columnList.size(); j++) {
					tmp.add(columnList.get(j).get(i));
				}
				colTable.add(new ColumnImpl(tmp, columnList.get(0).get(i)));
			}else {
				for(int k=0; k<columnList.size(); k++) {
					tmp.add(columnList.get(k).get(i));
				}
				colTable.add(new ColumnImpl(tmp));
			}
			tmp.clear();
		}
	}
	
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		int types[] = new int[3];
		sb.append("<csv.Table@" + Integer.toHexString(this.hashCode()) + ">\n");
		sb.append("RangeIndex: " + this.colTable.get(0).count() + " entries, 0 to " + (this.colTable.get(0).count()-1) + "\n");
		sb.append("Data columns (total " + (this.colTable.size()) + "columns):\n");
		sb.append(String.format("%3s | %12s | %14s | %s\n","#","Column","Non-Null Count","Dtype"));
		for(int j=0; j<this.colTable.size(); j++) {
			long t = this.colTable.get(0).count() - colTable.get(j).getNullCount();
			sb.append(String.format("%3s | %12s | ", j, colTable.get(j).header));
			String type = this.colTable.get(j).getDtype();
			switch(type) {
				case "double": types[0]++; break;
				case "int": types[1]++; break;
				case "String": types[2]++; break;
			}
			if(t == 0) {
				sb.append(String.format("%14s | %s \n", Long.toString(t) + " null", type));
			}else {
				sb.append(String.format("%14s | %s \n", Long.toString(t) + " non-null", type));
			}
		}
		sb.append(String.format("dtypes: double(%d), int(%d), String(%d)\n", types[0], types[1], types[2]));

		return sb.toString();
	}
	
	@Override
	public void print() {
		StringBuilder sb = new StringBuilder();
		if(colTable.get(0).header != null) {
			for (int i = 0; i < getColumnCount(); i++) {
				sb.append(String.format("%" + colTable.get(i).getColumnWidth() + "s | ", colTable.get(i).header));
			}
			sb.append("\n");
		}
		for(int i=0; i<getRowCount(); i++) {
			for(int j=0; j<getColumnCount(); j++) {
				sb.append(String.format("%" + colTable.get(j).getColumnWidth() + "s | ", colTable.get(j).getValue(i)));
			}
			sb.append("\n");
		}
		System.out.println(sb);
	}

	@Override
	public Table getStats() {
		List<ColumnImpl> columnList = new ArrayList<>();
		int idx = 1;
		
		if(!colTable.get(0).header.equals(null)) {
			columnList.add(new ColumnImpl(" "));
			columnList.get(0).addData("count");
			columnList.get(0).addData("mean");
			columnList.get(0).addData("std");
			columnList.get(0).addData("min");
			columnList.get(0).addData("25%");
			columnList.get(0).addData("50%");
			columnList.get(0).addData("75%");
			columnList.get(0).addData("max");
			for(ColumnImpl col: colTable) {
				if(col.getNumericCount() != 0) {
					columnList.add(new ColumnImpl(col.header));
					columnList.get(idx).addData(col.getNumericCount() + "");
					columnList.get(idx).addData(col.getMean() + "");
					columnList.get(idx).addData(col.getStd() + "");
					columnList.get(idx).addData(col.getNumericMin() + "");
					columnList.get(idx).addData(col.getQ1() + "");
					columnList.get(idx).addData(col.getMedian() + "");
					columnList.get(idx).addData(col.getQ3() + "");
					columnList.get(idx).addData(col.getNumericMax() + "");
					idx++;
				}
			}
		
		}else {
			columnList.add(new ColumnImpl());
			columnList.get(idx).addData("count");
			columnList.get(idx).addData("mean");
			columnList.get(idx).addData("std");
			columnList.get(idx).addData("min");
			columnList.get(idx).addData("25%");
			columnList.get(idx).addData("50%");
			columnList.get(idx).addData("75%");
			columnList.get(idx).addData("max");
			for(ColumnImpl col: colTable) {
				if(col.getNumericCount() != 0) {
					columnList.add(new ColumnImpl());
					columnList.get(idx).addData(col.getNumericCount() + "");
					columnList.get(idx).addData(col.getMean() + "");
					columnList.get(idx).addData(col.getStd() + "");
					columnList.get(idx).addData(col.getNumericMin() + "");
					columnList.get(idx).addData(col.getQ1() + "");
					columnList.get(idx).addData(col.getMedian() + "");
					columnList.get(idx).addData(col.getQ3() + "");
					columnList.get(idx).addData(col.getNumericMax() + "");
					idx++;
				}
			}
		}
		TableImpl table = new TableImpl(columnList);
    	return table;
	}

	@Override
	public Table head() {
		return selectRows(0, 5);
//		List<ColumnImpl> columnList = new ArrayList<>();
//		int idx = 0;
//		if(colTable.get(0).header != null) {
//			for(ColumnImpl col: colTable) {
//				columnList.add(new ColumnImpl(col.header));
//				for(int i=0; i<5; i++) {
//					columnList.get(idx).addData(col.getValue(i));
//				}
//				idx++;
//			}
//		}else {
//			for(ColumnImpl col: colTable) {
//				columnList.add(new ColumnImpl());
//				for(int i=0; i<5; i++) {
//					columnList.get(idx).addData(col.getValue(i));
//				}
//				idx++;
//			}
//		}
//		TableImpl table = new TableImpl(columnList);
//    	return table;
	}

	@Override
	public Table head(int lineCount) {
		return selectRows(0, lineCount);
//		List<ColumnImpl> columnList = new ArrayList<>();
//		int idx = 0;
//		if(colTable.get(0).header != null) {
//			for(ColumnImpl col: colTable) {
//				columnList.add(new ColumnImpl(col.header));
//				for(int i=0; i<lineCount; i++) {
//					columnList.get(idx).addData(col.getValue(i));
//				}
//				idx++;
//			}
//		}else {
//			for(ColumnImpl col: colTable) {
//				columnList.add(new ColumnImpl());
//				for(int i=0; i<lineCount; i++) {
//					columnList.get(idx).addData(col.getValue(i));
//				}
//				idx++;
//			}
//		}
//		TableImpl table = new TableImpl(columnList);
//    	return table;
	}

	@Override
	public Table tail() {
		return selectRows(getRowCount()-5, getRowCount());
//		List<ColumnImpl> columnList = new ArrayList<>();
//		int idx = 0;
//		if(colTable.get(0).header != null) {
//			for(ColumnImpl col: colTable) {
//				columnList.add(new ColumnImpl(col.header));
//				for(int i=col.count()-5; i<=col.count()-1; i++) {
//					columnList.get(idx).addData(col.getValue(i));
//				}
//				idx++;
//			}
//		}else {
//			for(ColumnImpl col: colTable) {
//				columnList.add(new ColumnImpl());
//				for(int i=col.count()-5; i<=col.count()-1; i++) {
//					columnList.get(idx).addData(col.getValue(i));
//				}
//				idx++;
//			}
//		}
//		TableImpl table = new TableImpl(columnList);
//    	return table;
	}

	@Override
	public Table tail(int lineCount) {
		return selectRows(getRowCount()-lineCount, getRowCount());
//		List<ColumnImpl> columnList = new ArrayList<>();
//		int idx = 0;
//		if(colTable.get(0).header != null) {
//			for(ColumnImpl col: colTable) {
//				columnList.add(new ColumnImpl(col.header));
//				for(int i=col.count()-lineCount; i<=col.count()-1; i++) {
//					columnList.get(idx).addData(col.getValue(i));
//				}
//				idx++;
//			}
//		}else {
//			for(ColumnImpl col: colTable) {
//				columnList.add(new ColumnImpl());
//				for(int i=col.count()-lineCount; i<=col.count()-1; i++) {
//					columnList.get(idx).addData(col.getValue(i));
//				}
//				idx++;
//			}
//		}
//		TableImpl table = new TableImpl(columnList);
//    	return table;
	}

	@Override
	public Table selectRows(int beginIndex, int endIndex) {
		List<ColumnImpl> columnList = new ArrayList<>();
		int idx = 0;
		if(colTable.get(0).header != null) {
			for(ColumnImpl col: colTable) {
				columnList.add(new ColumnImpl(col.header));
				for(int i=beginIndex; i<endIndex; i++) {
					columnList.get(idx).addData(col.getValue(i));
				}
				idx++;
			}
		}else {
			for(ColumnImpl col: colTable) {
				columnList.add(new ColumnImpl());
				for(int i=beginIndex; i<endIndex; i++) {
					columnList.get(idx).addData(col.getValue(i));
				}
				idx++;
			}
		}
		TableImpl table = new TableImpl(columnList);
    	return table;
	}

	@Override
	public Table selectRowsAt(int... indices) {
		List<ColumnImpl> columnList = new ArrayList<>();
		int idx = 0;
		if(colTable.get(0).header != null) {
			for(ColumnImpl col: colTable) {
				columnList.add(new ColumnImpl(col.header));
				for(int i=0; i<indices.length; i++) {
					columnList.get(idx).addData(col.getValue(indices[i]));
				}
				idx++;
			}
		}else {
			for(ColumnImpl col: colTable) {
				columnList.add(new ColumnImpl());
				for(int i=0; i<indices.length; i++) {
					columnList.get(idx).addData(col.getValue(indices[i]));
				}
				idx++;
			}
		}
		TableImpl table = new TableImpl(columnList);
    	return table;
		
	}

	@Override
	public Table selectColumns(int beginIndex, int endIndex) {
		List<ColumnImpl> columnList = new ArrayList<>();
		if(colTable.get(0).header != null) {
			for(int i=beginIndex; i<endIndex; i++) {
				columnList.add(new ColumnImpl(colTable.get(i).header));
				for(int j=0; j<colTable.get(i).count(); j++) {
					columnList.get(i).addData(colTable.get(i).getValue(j));
				}
			}
		}else {
			for(int i=beginIndex; i<endIndex; i++) {
				columnList.add(new ColumnImpl());
				for(int j=0; j<colTable.get(i).count(); j++) {
					columnList.get(i).addData(colTable.get(i).getValue(j));
				}
			}
		}
		TableImpl table = new TableImpl(columnList);
    	return table;
	}

	@Override
	public Table selectColumnsAt(int... indices) {
		List<ColumnImpl> columnList = new ArrayList<>();
		if(colTable.get(0).header != null) {
			for(int i=0; i<indices.length; i++){
				columnList.add(new ColumnImpl(colTable.get(indices[i]).header));
				for(int j=0; j<colTable.get(indices[i]).count(); j++) {
					columnList.get(i).addData(colTable.get(indices[i]).getValue(j));
				}
			}
		}else {
			for(int i=0; i<indices.length; i++){
				columnList.add(new ColumnImpl());
				for(int j=0; j<colTable.get(indices[i]).count(); j++) {
					columnList.get(i).addData(colTable.get(indices[i]).getValue(j));
				}
			}
		}
		TableImpl table = new TableImpl(columnList);
		return table;
	}

	@SuppressWarnings("unchecked")
	@Override
	public <T> Table selectRowsBy(String columnName, Predicate<T> predicate) {
		ColumnImpl newCol = (ColumnImpl) this.getColumn(columnName);
		List<Integer> table = new ArrayList<>();
		int arrInteger[];
		String tmp;
		
		for(int i=0; i<newCol.count(); i++) {
			try {
				tmp = newCol.getValue(i);
				if(tmp.equals("null")) tmp = null;
				if(predicate.test((T) tmp)) {
					table.add(i);
				}
			}catch(Exception e) {
				try {
					if(predicate.test((T) newCol.getValue(i, Double.class))) {
						table.add(i);
					}
				}catch(Exception e1) {
					try {
						if(predicate.test((T) newCol.getValue(i, Integer.class))) {
							table.add(i);
						}
					}catch(Exception e2) {
						
					}
				}
			}
			
		}
		arrInteger = table.stream().mapToInt(Integer::intValue).toArray();
		return selectRowsAt(arrInteger);
	}

	@Override
	public Table sort(int byIndexOfColumn, boolean isAscending, boolean isNullFirst) {
		if(this.colTable.get(byIndexOfColumn).getDtype().equals("int")){
			List<Integer> datas = new ArrayList<>();
			List<String> nulldatas = new ArrayList<>();
			List<String> convertdatas = new ArrayList<>();

			for(int i=0; i<this.colTable.get(byIndexOfColumn).count(); i++){
				if(this.colTable.get(byIndexOfColumn).getValue(i) == "null"){
					nulldatas.add("null");
					continue;
				}
				try{
					datas.add(Integer.parseInt(this.colTable.get(byIndexOfColumn).getValue(i)));
				}catch(NumberFormatException e) {

				}
			}
			Collections.sort(datas);
			for(int i=0; i<datas.size(); i++){
				convertdatas.add(Integer.toString(datas.get(i)));
			}
			if(!isAscending) {
				Collections.reverse(datas);
			}
			if(isNullFirst) {
				convertdatas.addAll(0, nulldatas);
			}else{
				convertdatas.addAll(nulldatas);
			}

			for(int i=0; i<this.colTable.get(byIndexOfColumn).count(); i++){
				this.colTable.get(byIndexOfColumn).setValue(i, convertdatas.get(i));
			}
		}else if(this.colTable.get(byIndexOfColumn).getDtype().equals("double")){
			List<Double> doubleDatas = new ArrayList<>();
			List<String> nulldatas = new ArrayList<>();
			List<String> convertdatas = new ArrayList<>();

			for(int i=0; i<this.colTable.get(byIndexOfColumn).count(); i++){
				if(this.colTable.get(byIndexOfColumn).getValue(i) == "null"){
					nulldatas.add("null");
					continue;
				}
				doubleDatas.add(Double.parseDouble(this.colTable.get(byIndexOfColumn).getValue(i)));
			}
			Collections.sort(doubleDatas);
			for(int i=0; i<doubleDatas.size(); i++){
				convertdatas.add(Double.toString(doubleDatas.get(i)));
			}
			for(int i=0; i<convertdatas.size(); i++){
				try{
					if(convertdatas.get(i).split("\\.")[1].equals("0")){
//						convertdatas.set(i, convertdatas.get(i).replace(".0",""));
						convertdatas.set(i, convertdatas.get(i).split("\\.")[0]);
					}
				}catch(ArrayIndexOutOfBoundsException e){
					continue;
				}
			}
			if(!isAscending) {
				Collections.reverse(convertdatas);
			}
			if(isNullFirst) {
				convertdatas.addAll(0, nulldatas);
			}else{
				convertdatas.addAll(nulldatas);
			}

			for(int i=0; i<this.colTable.get(byIndexOfColumn).count(); i++){
				this.colTable.get(byIndexOfColumn).setValue(i, convertdatas.get(i));
			}
		}else if(this.colTable.get(byIndexOfColumn).getDtype().equals("String")){
			List<Double> doubleDatas = new ArrayList<>();
			List<String> stringDatas = new ArrayList<>();
			List<String> nulldatas = new ArrayList<>();
			List<String> convertdatas = new ArrayList<>();

			for(int i=0; i<this.colTable.get(byIndexOfColumn).count(); i++){
				if(this.colTable.get(byIndexOfColumn).getValue(i) == "null"){
					nulldatas.add("null");
					continue;
				}
				try {
					doubleDatas.add(Double.parseDouble(this.colTable.get(byIndexOfColumn).getValue(i)));
				}catch(NumberFormatException e){
					stringDatas.add(this.colTable.get(byIndexOfColumn).getValue(i));
				}
			}
			Collections.sort(doubleDatas);
			Collections.sort(stringDatas);
			for(int i=0; i<doubleDatas.size(); i++){
				convertdatas.add(Double.toString(doubleDatas.get(i)));
			}
			for(int i=0; i<convertdatas.size(); i++){
				try{
					if(convertdatas.get(i).split("\\.")[1].equals("0")){
//						convertdatas.set(i, convertdatas.get(i).replace(".0",""));
						convertdatas.set(i, convertdatas.get(i).split("\\.")[0]);
					}
				}catch(ArrayIndexOutOfBoundsException e){
					continue;
				}
			}
			if(!isAscending) {
				Collections.reverse(convertdatas);
				Collections.reverse(stringDatas);
			}
			convertdatas.addAll(stringDatas);
			if(isNullFirst) {
				convertdatas.addAll(0, nulldatas);
			}else{
				convertdatas.addAll(nulldatas);
			}

			for(int i=0; i<this.colTable.get(byIndexOfColumn).count(); i++){
				this.colTable.get(byIndexOfColumn).setValue(i, convertdatas.get(i));
			}
		}
		return this;
	}

	@Override
	public Table shuffle() {
		List<Integer> randInteger = new ArrayList<>();
		Table originList = selectRows(0, getRowCount());

		for(int i=0; i<getRowCount(); i++){
			randInteger.add(i);
		}
		Collections.shuffle(randInteger);

		for(int i=0; i<getRowCount(); i++){
			for(int j=0; j<getColumnCount(); j++){
				getColumn(j).setValue(i, originList.getColumn(j).getValue(randInteger.get(i)));
			}
		}

		return this;
	}

	@Override
	public int getRowCount() {
		return colTable.get(0).count();
	}

	@Override
	public int getColumnCount() {
		return colTable.size();
	}

	@Override
	public Column getColumn(int index) {
		return this.colTable.get(index);
	}

	@Override
	public Column getColumn(String name) {
		for(Column col: this.colTable){
			if(col.getHeader().equals(name)){
				return col;
			}
		}
		return null;
	}

	@Override
	public boolean fillNullWithMean() {
		boolean flag = false;
		for(int i = 0; i < getColumnCount(); i++)
			if(getColumn(i).fillNullWithMean())
				flag = true;
		return flag;
	}

	@Override
	public boolean fillNullWithZero() {
		boolean flag = false;
		for(int i = 0; i < getColumnCount(); i++)
			if(getColumn(i).fillNullWithZero())
				flag = true;
		return flag;
	}

	@Override
	public boolean standardize() {
		boolean flag = false;
		for(var i = 0; i < getColumnCount(); ++i) {
			if(getColumn(i).standardize()) {
				flag = true;
			}
		}
		return flag;
	}

	@Override
	public boolean normalize() {
		boolean flag = false;
		for(var i = 0; i < getColumnCount(); ++i) {
			if(getColumn(i).normalize()) {
				flag = true;
			}
		}
		return flag;
	}

	@Override
	public boolean factorize() {
		boolean flag = false;
		for(var i = 0; i < getColumnCount(); ++i) {
			if(getColumn(i).factorize()) {
				flag = true;
			}
		}
		return flag;
	}

}