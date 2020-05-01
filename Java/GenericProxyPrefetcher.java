package com.example.util;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.function.Consumer;

class ReflectUtil
{
	private static <T extends BaseObject> 
	Field getField(Class<T> clazz, String memname) 
	{
		Field f = null;
		try {
			f = clazz.getDeclaredField(memname);
		} catch (NoSuchFieldException | SecurityException e) {
			e.printStackTrace();
			throw new RuntimeException(e);
		}
		f.setAccessible(true);
		return f;
	}
	
	@SuppressWarnings("unchecked")
	static <T extends BaseObject, U> 
	U getMember(T obj, String memname)
	{
		Field f = getField(obj.getClass(), memname);
		
		U member = null;
		try {
			member = (U) f.get(obj);
		} catch (IllegalArgumentException | IllegalAccessException e) {
			e.printStackTrace();
			throw new RuntimeException(e);
		}
		
		return member;
	}
	
	static <T extends BaseObject, U> 
	void setMember(T obj, String memname, U value)
	{
		Field f = getField(obj.getClass(), memname);
		
		try {
			f.set(obj, value);
		} catch (IllegalArgumentException | IllegalAccessException e) {
			e.printStackTrace();
			throw new RuntimeException(e);
		}
	}
	
	@SuppressWarnings("unchecked")
	static <T extends BaseObject, U extends BaseObject> 
	List<U> getList(T obj, String listname)
	{
		Field f = getField(obj.getClass(), listname);
		
		List<U> list = null;
		try {
			list = (List<U>) f.get(obj);
		} catch (IllegalArgumentException | IllegalAccessException e) {
			e.printStackTrace();
			throw new RuntimeException(e);
		}
		
		return list;
	}
	
	static <T extends BaseObject, U extends BaseObject> 
	int addToList(T obj, String listname, U element)
	{
		List<U> list = getList(obj, listname);
		if (list == null) {
			//initializeToMSATEquipmentProperties();
			String methodname = "initialize" + listname.substring(0,1).toUpperCase()+listname.substring(1);
			invokeMethod(obj, methodname);
			list = getList(obj, listname);
		}
		list.add(element);
		Field f = getField(obj.getClass(), listname);
		
		try {
			f.set(obj, list);
		} catch (IllegalArgumentException | IllegalAccessException e) {
			e.printStackTrace();
			throw new RuntimeException(e);
		}		
		return list.size();		
	}
	
	static Method getMethod(Class<?> clazz, String methodName) {
		Method method = null;
		try {
			method = clazz.getDeclaredMethod(methodName);
		} catch (NoSuchMethodException | SecurityException e) {
			e.printStackTrace();
			throw new RuntimeException(e);
		}
		method.setAccessible(true);
		return method;
	}
	
	static Method getMethod(Class<?> clazz, String methodName, Object... params)
	{
		while (clazz != null) {
			Method[] allMethods = clazz.getDeclaredMethods();
		    for (Method method : allMethods) {
					String mname = method.getName();
					if (!mname.equals(methodName)) { continue; }
					
					Class<?>[] args = method.getParameterTypes();
					if (args.length != params.length) { continue; }
					
					boolean argtypemismatch = false;
					
					for (int i=0; i < args.length; ++i) {
						if (! args[i].isAssignableFrom(params[i].getClass())) {
							argtypemismatch = true;
							break;
						}
					}
					
					if (argtypemismatch) { continue; }
			 		
		 			method.setAccessible(true);
		 			return method;
		    }
		    clazz = clazz.getSuperclass();
		}
		
		try {
			throw new NoSuchMethodException();
		} catch (NoSuchMethodException e) {
			e.printStackTrace();
			throw new RuntimeException(e);
		}
	}
	
	static Object invokeMethod(Object object, Method method) {
		try {
			Object returnedObj = method.invoke(object);
			return returnedObj;
		} catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e) {
			e.printStackTrace();
			throw new RuntimeException(e);
		}
		catch (Exception e) {
			e.printStackTrace();
			throw new RuntimeException(e);
		}
	}

	static void invokeMethod(Object object, Method method, Object... params) {
		try {
			method.invoke(object, params);
		} catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e) {
			e.printStackTrace();
			throw new RuntimeException(e);
		}
		catch (Exception e) {
			e.printStackTrace();
			throw new RuntimeException(e);
		}
	}
	
	static Object invokeMethod(Object object, String methodName)
	{	
		Method method = getMethod(object.getClass(), methodName);
		return invokeMethod(object, method);
	}
	
	static void invokeMethod(Object object, String methodName, Object... params)
	{	
		Method method = getMethod(object.getClass(), methodName, params);
		invokeMethod(object, method, params);
	}

	static Method getSetAttributesMethod() {
		String methodName = "SetAttributes";
		Method method = null;
		try {
			method = OMSAttributeParser.class.getMethod(methodName, DomainObj.class, BaseModel.class);
		} catch (NoSuchMethodException | SecurityException e) {
			e.printStackTrace();
			throw new RuntimeException(e);
		}
		return method;
	}
}

class ModelFuncUtils
{
	private final Method createParentModelMethod;
	private final String parentRelation;
	
	private Method setParentMethod = null;
	private String childRelation;
	private Method createChildModelMethod;
	private String childCountMember;
	
	private Method setBaseObjectObjectMethod = null;
	
	private final Method setAttrMethod = ReflectUtil.getSetAttributesMethod();
	private final OmsFactory modelFactory = OmsFactoryImpl.init();
	private final OmsFactory childModelFactory = OmsFactory.eINSTANCE;
	
	ModelFuncUtils(String classname, String parentrelation) {
		createParentModelMethod = ReflectUtil.getMethod(modelFactory.getClass(), "create" + classname);
		parentRelation = parentrelation;
		setBaseObjectObjectMethod = null;
	}
	
	void setChildMethods(String childclassname, String childrelation) {
		childRelation = childrelation;
		createChildModelMethod = ReflectUtil.getMethod(childModelFactory.getClass(), "create" + childclassname);
		childCountMember = childrelation + "Count";
		setParentMethod = null;
		setBaseObjectObjectMethod = null;
	}
	
	<Model extends BaseObject>
	void setAttributes(DomainObj ascObj, Model dbObject)
	{
		ReflectUtil.invokeMethod(null, setAttrMethod,ascObj, dbObject);
		dbObject.setOID(ascObj.getOID());
	}
	
	<Proxy extends BaseObjectProxy, Model extends BaseObject>
	void SetBaseObjectObject(Proxy proxy, Model model)
	{
		 if (setBaseObjectObjectMethod == null) {
         	setBaseObjectObjectMethod = ReflectUtil.getMethod(proxy.getClass(), "SetBaseObjectObject", model);
         }
         ReflectUtil.invokeMethod(proxy, setBaseObjectObjectMethod, model);
	}

	<Model extends BaseObject>
	Model  createModelWithAscObj(DomainObj ascObj)
	{
		@SuppressWarnings("unchecked")
		Model tmodelObj = (Model) ReflectUtil.invokeMethod(modelFactory, createParentModelMethod);
		setAttributes(ascObj, tmodelObj);
		return tmodelObj;
	}
	
	<Model extends BaseObject>
	Model  createChildModelWithAscObj(DomainObj ascObj)
	{
		@SuppressWarnings("unchecked")
		Model tmodelObj = (Model) ReflectUtil.invokeMethod(childModelFactory, createChildModelMethod);
		setAttributes(ascObj, tmodelObj);
		return tmodelObj;
	}
	
	<ParentModel extends BaseObject, ChildModel extends BaseObject> 
	void setParent(ChildModel childObj, ParentModel parentObj)
	{
		if (setParentMethod == null) {
			setParentMethod = ReflectUtil.getMethod(childObj.getClass(), "set" + parentRelation.substring(0, 1).toUpperCase() + parentRelation.substring(1), parentObj);
		}
		ReflectUtil.invokeMethod(childObj, setParentMethod, parentObj);
	}
	
	<ParentModel extends BaseObject, ChildModel extends BaseObject>  
	void addChild(ParentModel parentObj, ChildModel childObj)
	{
		int count = ReflectUtil.addToList(parentObj, childRelation, childObj);
		ReflectUtil.setMember(parentObj, childCountMember, count);
	}
	
	<ParentModel extends BaseObject, ChildModel extends BaseObject>  
	void clearChildren(ParentModel parentObj)
	{
		ReflectUtil.setMember(parentObj, childRelation, null);
	}
}

public final class BulkProxyPrefetcher <Model extends BaseObject, Proxy extends BaseObjectProxy> {
	
	private final List<Model> candidateObjects = new ArrayList<>();
	private final String className;
	private final String toRelation;
	
	private final ModelFuncUtils modelFuncUtils;
	
	private static final int MAX_NUM_OF_SRC_OIDS_IN_EACH_QUERY = 5000;
	private static final boolean SWITCH_OFF_FEATURE = false;

	private BulkProxyPrefetcher(final List<Model> objectlist, final String classname, final String relationstring) 
	{
		for (Model obj : objectlist) {
			if (obj == null || CASEOIDGenerator.isNewOID(obj.getOID())) { continue;}
			candidateObjects.add(obj);
		}
		className = classname;
		toRelation = relationstring;
		
		modelFuncUtils = new ModelFuncUtils(classname, toRelation);
	}
	
	public static <TModel extends BaseObject, TProxy extends BaseObjectProxy>
	BulkProxyPrefetcher<TModel, TProxy> createBulkPrefetcher (final List<TModel> proxylist, final String classname, final String relationstring) 
	{
		return new BulkProxyPrefetcher<TModel, TProxy>(proxylist, classname, relationstring);
	}
	
	public static <TModel extends BaseObject, TProxy extends BaseObjectProxy, UIModel extends UIBaseAttribute<TModel>>
	BulkProxyPrefetcher<TModel, TProxy> createBulkPrefetcherFromUIModels (final List<UIModel> uimodels, final String classname, final String relationstring) 
	{
		List<TModel> dbmodels = new ArrayList<>();
		for (UIModel uimodel: uimodels) {
			dbmodels.add(uimodel.getDBModel());
		}
		
		return createBulkPrefetcher(dbmodels, classname, relationstring);
	}
	
	public void bulkPrefetchAndResolveAllProxies() 
	{
		if (SWITCH_OFF_FEATURE){
			return;
		}
		Map<String, List<Proxy>> unresolvedProxies = filterUnresolvedProxies();
		
		if (unresolvedProxies.size() == 0) {
			return;
		}
		
		processObjectsFromDBInBulk(unresolvedProxies.keySet(), functionToBulkProcessProxies(unresolvedProxies));
	}
	
	private Map<String, List<Proxy>> filterUnresolvedProxies() 
	{
		Map<String, List<Proxy>> unresolvedProxies = new HashMap<>();
		for (Model proxyobj: candidateObjects) {
			
			if(proxyobj.getOID().equals("Insufficient Access") == true){
                throw new DomainException(DomainCommunicatorError.ERR_INSUFFICIENT_ACCESS, DomainCommunicatorError.ERR_DESC_INSUFFICIENT_ACCESS);
            }
			
			if (!(proxyobj instanceof BaseObjectProxy)) {
				continue;
			}
						
			@SuppressWarnings("unchecked")
			Proxy proxy = (Proxy) proxyobj;
			if (getModel(proxy) == null) {
				List<Proxy> proxyList = unresolvedProxies.get(proxyobj.getOID());
				if (proxyList == null) {
					unresolvedProxies.put(proxyobj.getOID(), new ArrayList<>());
					proxyList = unresolvedProxies.get(proxyobj.getOID());
				}
				proxyList.add(proxy);
			}	
		}
		return unresolvedProxies;
	}

	private void createModelsWithAscObjs(final Map<String, List<Proxy>> unresolvedProxies, final DomainObj[] ascObjs) 
	{
		for (int i=0; i < ascObjs.length; ++i) {
			DomainObj ascObj = ascObjs[i];
            Model model = modelFuncUtils.createModelWithAscObj(ascObj);
            
            List<Proxy> proxylist = unresolvedProxies.get(ascObj.getOID());            
			for (Proxy proxy : proxylist) {
	            setModel(proxy, model);
            }
		}
	}
	
	@SuppressWarnings("unchecked")
	public <ChildModel extends BaseObject> 
	void bulkPrefetchAndResolveAllChildren(final String childclass, final String childrelation) 
	{
		if (SWITCH_OFF_FEATURE){
			return;
		}
		modelFuncUtils.setChildMethods(childclass, childrelation);
		bulkPrefetchAndResolveAllProxies();
		Map <String, List<Model>> parentOidVsParentImpls = new HashMap<>();
		
		for (Model parentobj: candidateObjects) {
			Model parentModel = parentobj;
			if (parentModel instanceof BaseObjectProxy) {
				parentModel = getModel((Proxy) parentobj);
			}
			
			modelFuncUtils.clearChildren(parentModel);
			
			String parentOid = parentModel.getOID();
			
			List<Model> modelList = parentOidVsParentImpls.get(parentOid);
			
			if (modelList == null) {
				parentOidVsParentImpls.put(parentOid, new ArrayList<>());
				modelList = parentOidVsParentImpls.get(parentOid);
			}
			modelList.add(parentModel);
		}
		
		processObjectsFromDBInBulk(parentOidVsParentImpls.keySet(), 
									functionToBulkProcessChildren(parentOidVsParentImpls, childclass, childrelation));
	}

	private <ChildModel extends BaseObject>
	void createChildModelWithAscObjs(final Map<String, List<Model>> parentOidVsParentImpls, final DomainObj[] ascObjs) 
	{
		for (int i=0; i < ascObjs.length; ++i) {
			// Parent
			DomainObj parentAscObj = ascObjs[i];
            String parentOid = parentAscObj.getOID();
            
            ++i;
            
            // Child
            DomainObj childAscObj = ascObjs[i];
            
            List<Model> parentImpls = parentOidVsParentImpls.get(parentOid);
            
            //add Child for each parent impl.
            for (Model parentimpl: parentImpls){
            	ChildModel childModel = modelFuncUtils.createChildModelWithAscObj(childAscObj);
        		
        		modelFuncUtils.setParent(childModel, parentimpl);
        		
        		synchronized (parentimpl) {
        		    boolean deliver = parentimpl.eDeliver();
        		    try{
        		    	parentimpl.eSetDeliver(false);
        		    	modelFuncUtils.addChild(parentimpl, childModel);
        		    }finally{
        		    	parentimpl.eSetDeliver(deliver);
        		    }
        		}
            }  // End of For each parentimpl.
		}
	}
	
	private void setModel(Proxy proxy, Model model)
	{
		ReflectUtil.setMember(proxy, toRelation, model);
		modelFuncUtils.SetBaseObjectObject(proxy, model);
	}
	
	private Model getModel(Proxy object) {		
		return ReflectUtil.getMember(object, toRelation);
	}
	
	private static List<List<String>> splitListIntoChunks(final List<String> unresolvedObjects)
	{
		List<List<String>> splittedList = new ArrayList<>();
		int startIndex = 0;
		for (; (startIndex + MAX_NUM_OF_SRC_OIDS_IN_EACH_QUERY) < unresolvedObjects.size(); startIndex += MAX_NUM_OF_SRC_OIDS_IN_EACH_QUERY) {
			splittedList.add(unresolvedObjects.subList(startIndex, startIndex + MAX_NUM_OF_SRC_OIDS_IN_EACH_QUERY));
		}
		
		splittedList.add(unresolvedObjects.subList(startIndex, unresolvedObjects.size()));
		
		return splittedList;
		
	}
	
	private static void processObjectsFromDBInBulk(final Set<String> srcOids, Consumer<List<String>> funcToBulkProcess) 
	{
		List<List<String>> splittedList = splitListIntoChunks(new ArrayList<>(srcOids));
		splittedList.parallelStream().forEach(funcToBulkProcess);
	}
	
	private Consumer<List<String>> functionToBulkProcessProxies(final Map<String, List<Proxy>> unresolvedProxies) 
	{
		return srcOids -> {
			DomainObj[] ascObjs = CASEPluginService.getObjects(srcOids);
			if (ascObjs != null) {
				createModelsWithAscObjs(unresolvedProxies, ascObjs);				
			}
		};
	}
	
	private Consumer<List<String>> functionToBulkProcessChildren(final Map<String, List<Model>> parentOidVsParentImpls, final String childClassName, final String childRelation) 
	{
		return srcOids -> {
			DomainObj[] ascObjs = CASEPluginService.getChildrenForMultipleObjects(srcOids, className, childClassName, childRelation);
			if (ascObjs != null) {
				createChildModelWithAscObjs(parentOidVsParentImpls, ascObjs);				
			}
		};
	}
}
