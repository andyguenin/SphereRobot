package com.revo.logging;


import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

import com.revo.logging.LoggerI;

/**
 * Collection of logs that allows you to perform operations on all logs at once
 * @author Andrew McAleer
 * @version 01/24/2012
 */
public class LogCollection implements Collection<LoggerI>{

	private ArrayList<LoggerI> logs;
	
	/**
	 * Creates a new log collection
	 */
	public LogCollection()
	{
		logs = new ArrayList<LoggerI>();
	}
	
	
	/**
	 * Adds a logger to the collection
	 * @param log the log to add to the collection
	 */
	@Override
	public boolean add(LoggerI log) {
	
		return logs.add(log);
		
	}

	/**
	 * Adds a collection of logs to this collection
	 * @param logCollection the collection of logs to add
	 */
	@Override
	public boolean addAll(Collection<? extends LoggerI> logCollection) {
		
		return logs.addAll(logCollection);
		
	}

	@Override
	public void clear() {
		logs.clear();
		
	}

	@Override
	public boolean contains(Object arg0) {
		
		return logs.contains(arg0);
	}

	@Override
	public boolean containsAll(Collection<?> arg0) {
		
		return logs.containsAll(arg0);
	}

	@Override
	public boolean isEmpty() {
		
		return logs.isEmpty();
	}

	@Override
	public Iterator<LoggerI> iterator() {
		
		return logs.iterator();
	}

	@Override
	public boolean remove(Object arg0) {
		
		return logs.remove(arg0);
	}

	@Override
	public boolean removeAll(Collection<?> arg0) {
		
		return logs.removeAll(arg0);
	}

	@Override
	public boolean retainAll(Collection<?> arg0) {
		
		return logs.retainAll(arg0);
	}

	@Override
	public int size() {
		
		return logs.size();
	}

	@Override
	public Object[] toArray() {
		
		return logs.toArray();
	}

	@Override
	public <T> T[] toArray(T[] arg0) {
		
		return logs.toArray(arg0);
	}
	
	public void logText(String message)
	{
		Iterator<LoggerI> it = logs.iterator();
		while(it.hasNext())
			it.next().logText(message);
	}
	
	public void logWarning(String message)
	{
		Iterator<LoggerI> it = logs.iterator();
		while(it.hasNext())
			it.next().logWarning(message);
	}
	
	public void logError(String message)
	{
		Iterator<LoggerI> it = logs.iterator();
		while(it.hasNext())
			it.next().logError(message);
	}
	
	public void logStackTrace(StackTraceElement[] element)
	{
		Iterator<LoggerI> it = logs.iterator();
		while(it.hasNext())
			it.next().logStackTrace(element);
	}
	
}
