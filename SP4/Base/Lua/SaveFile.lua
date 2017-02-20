function SavePlayerFile(PlayerTag, Information)

	local FilePath = ("Lua//PlayerSave" .. PlayerTag .. ".lua");
	print("Saving to File PlayerSave" .. PlayerTag);
	local file = assert(io.open(FilePath, "w"));
	file:write(Information);
	file:close();
	print("Saving Complete")

end