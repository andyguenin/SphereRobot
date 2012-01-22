package com.spherebot.logging;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

public class LogCollection implements Collection<LoggerI>{

	ArrayList<LoggerI> log;
	
	public LogCollection()
	{
		log = new ArrayList<LoggerI>();
	}
	
	@Override
	public boolean add(LoggerI arg0) {
	
		return log.add(arg0);
		
	}

	@Override
	public boolean addAll(Collection<? extends LoggerI> arg0) {
		
		return log.addAll(arg0);
		
	}

	@Override
	public void clear() {
		log.clear();
		
	}

	@Override
	public boolean contains(Object arg0) {
		
		return log.contains(arg0);
	}

	@Override
	public boolean containsAll(Collection<?> arg0) {
		
		return log.containsAll(arg0);
	}

	@Override
	public boolean isEmpty() {
		
		return log.isEmpty();
	}

	@Override
	public Iterator<LoggerI> iterator() {
		
		return log.iterator();
	}

	@Override
	public boolean remove(Object arg0) {
		
		return log.remove(arg0);
	}

	@Override
	public boolean removeAll(Collection<?> arg0) {
		
		return log.removeAll(arg0);
	}

	@Override
	public boolean retainAll(Collection<?> arg0) {
		
		return log.retainAll(arg0);
	}

	@Override
	public int size() {
		
		return log.size();
	}

	@Override
	public Object[] toArray() {
		
		return log.toArray();
	}

	@Override
	public <T> T[] toArray(T[] arg0) {
		
		return log.toArray(arg0);
	}
	
	public void logText(String message)
	{
		Iterator<LoggerI> it = log.iterator();
		while(it.hasNext())
			it.next().logText(message);
	}
	
	public void logWarning(String message)
	{
		Iterator<LoggerI> it = log.iterator();
		while(it.hasNext())
			it.next().logWarning(message);
	}
	
	public void logError(String message)
	{
		Iterator<LoggerI> it = log.iterator();
		while(it.hasNext())
			it.next().logError(message);
	}
	
	public void logStackTrace(StackTraceElement[] element)
	{
		Iterator<LoggerI> it = log.iterator();
		while(it.hasNext())
			it.next().logStackTrace(element);
	}
	
}
