local function part1()
  local disk_raw = io.open("input.txt"):read()
  local disk = {}
  local pos = 0
  for i = 1, #disk_raw do
    local length = tonumber(disk_raw:sub(i, i))
    while length ~= 0 do
      if i % 2 == 1 then
        local id = math.floor(i / 2)
        disk[pos] = id
      else
        disk[pos] = '.'
      end
      pos = pos + 1
      length = length - 1
    end
  end

  local lp = 0
  local rp = pos-1;
  while (lp < rp) do
    if disk[lp] == '.' and disk[rp] ~= '.' then
      disk[lp] = disk[rp]
      disk[rp] = '.'
      lp = lp + 1
      rp = rp - 1
    end
    if disk[rp] == '.' then
      rp = rp - 1
    end
    if disk[lp] ~= '.' then
      lp = lp + 1
    end
  end
  local result = 0
  for idx, value in pairs(disk) do
    if disk[idx] ~= '.' then
      result = result + (idx*value)
    end
  end
  return result
end

print(part1())
