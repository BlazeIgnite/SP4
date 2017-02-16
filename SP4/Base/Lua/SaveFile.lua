function SavePlayerFile(local SaveFileValue, local Information)
{
	local FilePath = "Lua//PlayerSave" + SaveFileValue + ".lua";
	print("Saving to File PlayerSave" + SaveFileValue);
	local file = assert(io.open(FilePath, "w"));
	file:write(Information);
	file:close();
	print("Saving Complete")
}